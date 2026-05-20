#include "EntityController.hh"


void EntityController::Update(Entity* entity, const Input &input, float dt) {

    if (!entity) return;

    if (!input.IsActionDown(Action::MoveCamera)) {
        float x = input.deltaY * rotSpeed * -1;
        float y = input.deltaX * rotSpeed * -1;
        entity->transform.AddRotation({x, y, 0.0f});
    }

    if (input.IsActionDown(Action::ZoomIn)) {
        entity->transform.ScaleBy({dt});
    }
    if (input.IsActionDown(Action::ZoomOut)) {
        entity->transform.ScaleBy({-dt});
    }
}