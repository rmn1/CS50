<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = [];
    
    $search_terms = preg_split("/[\s,]+/", $_GET["geo"]);
    $search_terms_len = count($search_terms);
    
    $sql_query = "SELECT * FROM places WHERE ";
    
    for ($i = 0; $i < $search_terms_len; $i++) 
    {
        // state abbrev or admin_code2
        if (strlen($search_terms[$i]) <=2 )
        {
            $sql_query .= "admin_code1 LIKE '" . $search_terms[$i] . "%'";
        }
        // if longer numeric --> zip code
        elseif (is_numeric($search_terms[0])) 
        {
            $sql_query .= "postal_code LIKE '" . $search_terms[$i] . "%'";
        }
        // city name or state name
        else
        {
            $sql_query .= "(place_name LIKE '" . $search_terms[$i] . "%' OR " . 
                        "admin_name1 LIKE '" . $search_terms[$i] . "%')";
        }
    }
    
    $places = CS50::query($sql_query . " LIMIT 50");

    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>