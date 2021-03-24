from django.db import models
from apps.menus.models import Menu

# Create your models here.
class Commandes(models.Model):
    id = models.AutoField(primary_key=True)
    email = models.CharField(max_length=30)
    plate = models.ForeignKey(
            'menus.Menu',
            on_delete = models.CASCADE,
            )
    states = [
            (1, 'Recu'),
            (2, 'En Train de Faire'),
            (3, 'Pret a Retirer'),
            ]
    state = models.IntegerField(
            choices = states,
            default = 1,
            )
    created =  models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return "%s->%s: %s"%(self.id, self.email, self.plate.name)
