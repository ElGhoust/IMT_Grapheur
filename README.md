# IMT_Grapheur

## Comment utiliser les branches ?

### 1) Se connecter à une branche

    git checkout <branche>

### 2) Mettre à jour sa branche avec la branche master

    git stash
    git checkout master
    git pull
    git checkout <branche>
    git rebase master
    git stash pop