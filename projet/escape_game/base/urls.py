from django.urls import path, include
from .views import authView, home, action_led



urlpatterns = [
 path("", home, name="home"),
 path('action/<str:etat>/', action_led, name='action_led'),
 path("signup/", authView, name="authView"),
 path("accounts/", include("django.contrib.auth.urls")),
]
