<?php

    require("../includes/config.php"); 

    $rows = CS50::query("SELECT * FROM history WHERE user_id = ?", $_SESSION["id"]);

    $transactions = [];
    foreach ($rows as $row)
    {
        $transactions[] = [
            "transaction" => $row["transaction"],
            "time" => $row["time"],
            "symbol" => $row["symbol"],
            "shares" => $row["shares"],
            "price" => $row["price"],
        ];
    }

    render("history_form.php", ["transactions" => $transactions, "title" => "Transactions History"]);
   
?>
