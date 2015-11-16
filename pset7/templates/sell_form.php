<form action="sell.php" method="post">
    <fieldset>
        <select name="sellstock" id="sellstock">
            <option selected="selected"></option>
            <?php
                foreach($stocks as $stock) {?>
                    <option value="<?= $stock['symbol'] ?>"><?= $stock['symbol'] ?></option>
            <?php
             } ?>
        </select>
        <div class="form-group">
            <button type="sell" class="btn btn-default">Sell</button>
        </div>
    </fieldset>
</form>
