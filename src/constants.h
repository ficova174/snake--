#pragma once

// Screen dimensions
constexpr float screenHeight {800.0f};
constexpr float screenWidth {1200.0f};

// Map dimensions
float mapHeight;
float mapWidth;

// viewport settings
constexpr float viewportSpeed {20.0f};
constexpr float zoomSpeed {20.0f};
constexpr float aspectRatio = screenHeight/screenWidth;
