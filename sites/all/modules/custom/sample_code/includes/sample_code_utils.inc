<?php

function contact_load_util($conditions = array()) {
  $query = db_select(CONTACT_V1_TABLE, 'cv1');
  $query->fields('cv1');

  foreach ($conditions as $field => $value) {
    $query->condition($field, $value);
  }

  return $query->execute()->fetchAll();
}

function build_action($row) {
  $attributes = array('attributes' => array('class' => array('button')));
  $edit_link = l( t('Edit'), "sample_code/v1/contact/{$row->cid}/edit", $attributes );
  $delete_link = l( t('
    Delete'), "sample_code/v1/contact/{$row->cid}/delete", $attributes );
  $view_link = l( t('
    View'), "sample_code/v1/contact/{$row->cid}/view", $attributes );
  $action['actions'] = $view_link . ' '. $edit_link . ' ' . $delete_link ;
  return $action;
}


function contact_delete_util($conditions = array()) {
  $query = db_delete(CONTACT_V1_TABLE);

  foreach ($conditions as $field => $value) {
    $query->condition($field, $value);
  }

  return $query->execute();
}

