<?php



/**
 *  Implements hook_preprocess_node().
 *  @todo  needs works
 */

function my_custom_theme_preprocess_node(&$variables) {

  if (array_key_exists(NODE_IMAGE_FIELD_NAME, $variables['content'])) {

      if ( array_key_exists(NODE_IMAGE_STYLE_FIELD, $variables['content'])) {
        $image_style = isset($variables['content'][NODE_IMAGE_STYLE_FIELD]['#items'][0]['value']) ?
        $variables['content'][NODE_IMAGE_STYLE_FIELD]['#items'][0]['value'] : '';
      }  else if ($variables['node']->bundle == NODE_SUBTYPE) {
        $image_style = 'thumbnail';
      }
      if (!empty($image_style) && $image_style != 'no_image') {
        $variables['content'][NODE_IMAGE_FIELD_NAME][0]['#image_style'] = $image_style;
      } else if ($image_style == 'no_image') {
        unset($variables['content'][NODE_IMAGE_FIELD_NAME]);
      }
    }
}




