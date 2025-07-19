#pragma once

// Screen dimensions
constexpr float screenHeight{800.0f};
constexpr float screenWidth{1200.0f};

// Map dimensions
float mapHeight;
float mapWidth;

// viewport settings
constexpr float viewportSpeed{500.0f};
constexpr float zoomSpeed{3.0e3f};
constexpr float aspectRatio = screenHeight/screenWidth;

// Snake settings
constexpr float snakeSpeed{100.0f};
constexpr float snakeDashSpeed{200.0f};
constexpr float snakeRotationSpeed{300.0f};
float snakeAngle{0.0f};
