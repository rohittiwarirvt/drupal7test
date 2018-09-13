<?php





function my_custom_theme_preprocess_entity(&$variables) {
  switch ($variables['entity_type']) {
    case 'paragraphs_item':
      if (array_key_exists(PARAGRAPH_ITEM_IMAGE_FIELD_NAME, $variables['content'])) {

        if ( array_key_exists(PARAGRAPH_ITEM_IMAGE_STYLE, $variables['content'])) {
          $image_style = isset($variables['content'][PARAGRAPH_ITEM_IMAGE_STYLE]['#items'][0]['value']) ?
          $variables['content'][PARAGRAPH_ITEM_IMAGE_STYLE]['#items'][0]['value'] : '';
        }

        if (!empty($image_style)) {
          $variables['content'][PARAGRAPH_ITEM_IMAGE_FIELD_NAME][0]['#image_style'] = $image_style;
        } else {
          unset($variables['content'][PARAGRAPH_ITEM_IMAGE_FIELD_NAME]);
        }
      }
      break;

    default:
      # code...
      break;
  }
}




