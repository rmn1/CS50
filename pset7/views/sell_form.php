<form action="sell.php" method="post">
    <fieldset>
        <div class="form-group">
            <select class="form-control" name="symbol">
                <option disabled selected value="">Symbol</option>
                <?php foreach ($positions as $position): ?>
                    <option value='<?=$position["symbol"]?>'><?=strtoupper($position["symbol"])?></option>
                <?php endforeach; ?>
            </select> 
        </div>
        <div class="form-group">
            <input class="form-control" name="share_amt" placeholder="Number of Shares" type="text"/>
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">Sell</button>
        </div>
    </fieldset>
</form>