<div>
    Current funds:&nbsp;&nbsp;<b><?= "$" . number_format($_SESSION["cash"], 2) ?></b><br/>
    <br/>

    <form action="deposit.php" method="post">
        <fieldset>
            <div class="form-group">
                <input autofocus class="form-control" name="funds" placeholder="Add funds, e.g. 100.25" type="text"/>
            </div>
            <div class="form-group">
                <button type="submit" class="btn btn-default">Deposit</button>
            </div>
        </fieldset>
    </form>
</div>
