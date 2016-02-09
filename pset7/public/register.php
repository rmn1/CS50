<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // make sure a user name is entered
        if (empty($_POST["username"]))
        {
            apologize("Please enter a valid user name.");
        }
        // make sure the username does not already exist
        elseif (!empty(CS50::query("SELECT * FROM users WHERE username=?", $_POST["username"])))
        {
            apologize("The username " . $_POST["username"] . " is unavailable.");
        }
        // make sure a password is entered
        elseif (empty($_POST["password"]))
        {
            apologize("Please enter a valid password.");
        }
        // make sure password and confirmation are the same
        elseif ($_POST["password"] !== $_POST["password-confirm"])
        {
            apologize("The passwords you entered do not match.");
        }
        // if all tests passed, enter user into database
        else
        {
            CS50::query("INSERT IGNORE INTO users (username, hash, cash) VALUES(?, ?, 10000.0000)", $_POST["username"], password_hash($_POST["password"], PASSWORD_DEFAULT));
            $rows = CS50::query("SELECT LAST_INSERT_ID() AS id");
            $id = $rows[0]["id"];
            $_SESSION["id"] = $id;
            redirect("/");
        }
    }

?>