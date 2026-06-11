import typhoon.api.hil as hil
from typhoon.api.schematic_editor import model

def exec(**kwargs):
    model_path = "../Simulations/BLDC - Vel control with Current control.tse"

    mod= model.load(model_path)

    PID_2 = model.get_item("PID controller2")
    # print(model.get_property_values(PID_2))
    model.set_property_value(model.prop(PID_2, "kp"), round(kwargs.get("Kp_i"), 6))
    model.set_property_value(model.prop(PID_2, "ki"), round(kwargs.get("Ki_i"), 6))

    print(model.get_property_values(PID_2))
    model.save()
    model.close_model()