from django.db import models

class Device(models.Model):
    ip_address = models.CharField(max_length=100)

    def __str__(self):
        return self.ip_address
