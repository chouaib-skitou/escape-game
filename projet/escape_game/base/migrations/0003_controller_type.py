# Generated by Django 5.0.2 on 2024-04-24 12:17

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('base', '0002_controller'),
    ]

    operations = [
        migrations.AddField(
            model_name='controller',
            name='type',
            field=models.CharField(choices=[('sensor', 'Sensor'), ('button', 'Button'), ('other', 'Other')], default='other', max_length=100),
        ),
    ]
