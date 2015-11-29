<?php

    require(__DIR__ . "/../includes/config.php");
     
    // get an trimmed array of the parameters
    $parameters = array_map('trim', explode(",", urldecode($_GET["geo"])));
    
    // remove "US" parameter from all elements in the array
    if (($i = array_search("US", $parameters)) !== false) {
        unset($parameters[$i]);
    }    
    
    // builds a SQL statement
    $sql = "SELECT * FROM places WHERE ";
    for ($i = 0, $count = count($parameters); $i < $count; $i++) {
        // assume postal code if parameter is numeric
        if (is_numeric($parameters[$i])){
            $sql .= 'postal_code LIKE "' . $parameters[$i] . '%"';
            
        } else {
            $sql .= '(place_name  LIKE "' . $parameters[$i] . '%" OR ' . 
                    (strlen($parameters[$i]) <= 2 ? 'admin_code1 LIKE "' . $parameters[$i] . '%" OR ' : "") . 
                    'admin_name1 LIKE "' . $parameters[$i] . '%")';
        }
        
        if ($i < ($count - 1)) {
            $sql .= " AND ";
        }
    }
    
    $places = query($sql);
    
    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));
    
?>
