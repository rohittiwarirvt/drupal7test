<?php


function sample_code_add_contact_v1($form, &$form_state, $contact = array()) {
   $form['first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('First Name'),
    '#required' => TRUE,
    '#default_value' => isset($contact['first_name']) ? $contact['first_name']: "" ,
    '#description' => 'Please Insert First Name'
  );
  $form['last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Last Name'),
    '#default_value' => isset($contact['last_name']) ? $contact['last_name']: "" ,
    '#required' => TRUE,
    '#description' => 'Please Insert Last Name'
  );
  $form['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email '),
    '#default_value' => isset($contact['email']) ? $contact['email']: "" ,
    '#required' => TRUE,
    '#description' => 'Please Insert Email'
  );
  $form['phone_number'] = array(
    '#type' => 'textfield',
    '#title' => t('Phone Number'),
    '#default_value' => isset($contact['phone_number']) ? $contact['phone_number']: "" ,

    '#required' => TRUE,
    '#description' => 'Please Insert Phone Number'
  );
  $form['status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Is Active.'),
    '#default_value' => isset($contact['status']) ? $contact['status']: "" ,
    '#description' => 'Is this to be Published'
  );
  $form['action'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );


  if (isset($contact['cid'])) {

    $form['#submit'][] = 'sample_code_edit_contact_v1_submit';
    $form['action']['#value'] = 'Update';

    $form['cid'] = array(
      '#type' => 'value',
      '#value' => $contact['cid']
    );

  }
  return $form;
}

function sample_code_add_contact_v1_validate($forms, $form_state) {

}

function sample_code_add_contact_v1_submit($form, &$form_state) {
  global $user;
  $transaction = db_transaction();
  try {
    $query = db_insert(CONTACT_V1_TABLE)
        ->fields( array(
          'first_name' => $form_state['values']['first_name'],
          'last_name' =>  $form_state['values']['last_name'],
          'phone_number' =>  $form_state['values']['phone_number'],
          'email'=> $form_state['values']['email'],
          'status' => $form_state['values']['status'],
           'uid' => $user->uid
           ))
        ->execute();


  } catch (Exception $e) {

    $transaction->rollback();
    drupal_set_message(t('contact insert failed. Message @message', array('@message' => $e->getMessage())), 'error');
  }
  $name = $form_state['values']['first_name'] .' ' . $form_state['values']['last_name'];
  drupal_set_message(t('Successfull inserted contact @name', array('@name' => $name)), 'status');
}

function sample_code_edit_contact_v1($contact) {
  drupal_set_title(t('<em> Edit </em> @contact Id - @id ', array('@contact' => $contact->first_name . ' ' . $contact->last_name, '@id' => $contact->cid)), PASS_THROUGH);
  return drupal_get_form('sample_code_add_contact_v1', (array)$contact);
}


function sample_code_edit_contact_v1_submit($form, &$form_state) {
  $fields = array(
      'first_name' => $form_state['values']['first_name'],
      'last_name' =>  $form_state['values']['last_name'],
      'phone_number' =>  $form_state['values']['phone_number'],
      'email'=> $form_state['values']['email'],
      'status' => $form_state['values']['status'],
       );
  $cid = $form_state['values']['cid'];
  try {
    $count = db_update(CONTACT_V1_TABLE)
             -> fields($fields)
             ->condition('cid', $cid)
             ->execute();
   } catch( Exceptin $e) {
     drupal_set_message(t('contact update failed. Message @message', array('@message' => $e->getMessage())), 'error');
   }

   drupal_set_message(t('Contact updated successfully'),'status');
}

function sample_code_delete_contact_v1($form, $form_state, $contact) {
  $form['#contact'] = $contact;
  $form['cid'] = array(
    '#type' => 'value',
    '#value' => $contact->cid
    );
  $name = $contact->first_name.' ' .$contact->last_name;
  return confirm_form($form,
     t('Are you sure you want to deletle the %name contact ?', array('%name' => $name)),
      'sample_code/v1/contact/'.$contact->cid,
       t('This action cannot be undone.'),
        t('Delete'),
         t('Cancel')
    );
}


function sample_code_delete_contact_v1_submit($form, &$form_state) {
  module_load_include('inc', 'sample_code_v1', 'includes/sample_code_contact_v1.utils');

  if ( $form_state['values']['confirm']) {
    try {
      contact_delete_util(array('cid' => $form_state['values']['cid']));
      $form_state['redirect'] = '/sample_code/v1/contact';
    } catch (Exception $e) {
      drupal_set_message(t('Unable to delete a contact. Message @message', array('@message' => $e->getMessage())), 'error');
    }
    drupal_set_message(t('Contact deleted successfully'),'status');

  }
}

function sample_code_list_all_contact_v1() {
  module_load_include('inc', 'sample_code_v1', 'includes/sample_code_contact_v1.utils');
  $query = db_select(CONTACT_V1_TABLE, 'cv1')
            ->fields('cv1', array('cid', 'first_name','last_name'))
            ->addTag('node_access');

  $result = $query->execute()->fetchAll();


  $header = array(
    array( 'data' => t('Id'), 'field' => 'cv1.cid'),
    array( 'data' => t('First Name'), 'field' => 'cv1.first)name'),
    array( 'data' => t('Last name'), 'field' => 'cv1.last_name'),
    array( 'data' => t('Actions'))
    );
  $rows = array();
  foreach ($result as  $row) {
    $action = build_action($row);
    $rows_data = array_merge((array) $row, $action );
    $rows[] = array('data' => $rows_data );
  }
  $output = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    );
  return $output;
}


function sample_code_show_contact_v1($contact) {
  $build = array(
    '#theme' => 'sample_code_v1_show_contact',
    '#contact' => $contact,
  );

  return $build;
}
