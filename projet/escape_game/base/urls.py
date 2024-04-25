from django.urls import path, include
from .views import home, controller_create, update_device_ip, control_door, control_sensor, authView, controller_delete, controller_edit
from .views import authView, home, control_door, control_sensor
from .views import update_device_ip
from .views import video_feed



urlpatterns = [
 path("", home, name="home"),
 path('api/update_ip', update_device_ip, name='update_ip'),
path('action/door_<int:door_number>/<str:action>/', control_door, name='control_door'),
path('status/sensor_<int:sensor_number>/', control_sensor, name='control_sensor'),
 path("signup/", authView, name="authView"),
 path("accounts/", include("django.contrib.auth.urls")),
]
