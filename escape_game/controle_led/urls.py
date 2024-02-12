from django.urls import path
from . import views

urlpatterns = [
    path('', views.index, name='index'),
    path('action/<str:etat>/', views.action_led, name='action_led'),
]
