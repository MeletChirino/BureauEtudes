from django.db import models

# Create your models here.
class Menu(models.Model):
    name = models.CharField(max_length = 16)
    price = models.IntegerField()

    def __str__(self):
        return "%s"%(self.name)
