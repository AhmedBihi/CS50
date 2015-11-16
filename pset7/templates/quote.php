<form action="quote.php" method="post">
    <fieldset>
        <div class="form-group">
            <output class="form-control" name="symbol" type="text"/>
        <?php
            $s = lookup($_POST["symbol"]);
            print("Price ". number_format($s["price"], 4));
        ?>   
        </div>
    </fieldset>
</form>
