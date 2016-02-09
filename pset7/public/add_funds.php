<?php

    require("../includes/config.php"); 
    $id = $_SESSION["id"];

    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("add_funds_form.php", ["title" => "Deposit Funds"]);
    }
    else
    {
        if (empty($_POST["deposit"]) || !is_numeric($_POST["deposit"]))
        {
            apologize("Please enter a valid amount.");
        }
        
        elseif ($_POST["deposit"] > 5000)
        {
            apologize('You may only deposit $5,000 at this time');
        }

        $deposit = $_POST["deposit"];

        CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $deposit, $id);

       redirect("/");
    }

?>
