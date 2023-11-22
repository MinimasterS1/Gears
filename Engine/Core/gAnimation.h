#pragma once

#include <vector>

struct AnimationFrame {
    // информация о положении, вращении и масштабе костей
};

class Animation {
public:
    std::vector<AnimationFrame> frames;
    float startTime;
    float endTime;

    Animation() : startTime(0.0f), endTime(0.0f) {}
};


class AnimationPlayer {
private:
    Animation* currentAnimation;
    float currentTime;

public:
    void PlayAnimation(Animation* animation) {
        currentAnimation = animation;
        currentTime = animation->startTime;
    }

    void Update(float deltaTime) {
        if (currentAnimation) {
            currentTime += deltaTime;

            // Логика интерполяции и обновления костей
            // ...

            if (currentTime > currentAnimation->endTime) {
                // Анимация завершена
                currentAnimation = nullptr;
            }
        }
    }

    void StopAnimation() {
        currentAnimation = nullptr;
    }
};