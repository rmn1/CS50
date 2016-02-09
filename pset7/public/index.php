<?php

    require("../includes/config.php"); 

    $rows = CS50::query("SELECT symbol, shares FROM portfolios WHERE user_id = ?", $_SESSION["id"]);

    $positions = [];
    $total_value = 0;
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "symbol" => $row["symbol"],
                "price" => $stock["price"],
                "shares" => $row["shares"],
            ];
        }
        $total_value = $total_value + $row["shares"] * $stock["price"];
    }

    $cash_balance = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
    foreach ($cash_balance as $item){
        $cash_bal = $item["cash"];}
    
    render("portfolio.php", ["positions" => $positions, "title" => "Portfolio", "cash_balance" => $cash_bal, "total_value" => $total_value]);    
   
?>
