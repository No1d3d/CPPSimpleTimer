#include "raylib.h"
#include <chrono>
#include <ctime>
#include <vector>
#include <fstream>
#include <iomanip>
#include <sstream>

struct Measurement {
    std::string timeString;
};

std::string formatTime(std::chrono::milliseconds ms) {
    using namespace std::chrono;
    auto days = duration_cast<std::chrono::hours>(ms).count() / 24;
    auto hours = (ms.count() / (1000 * 60 * 60)) % 24;
    auto minutes = (ms.count() / (1000 * 60)) % 60;
    auto seconds = (ms.count() / 1000) % 60;
    auto milliseconds = (ms.count() / 10) % 100;

    std::ostringstream oss;
    oss << days << " | "
        << std::setw(2) << std::setfill('0') << hours << ":"
        << std::setw(2) << std::setfill('0') << minutes << ":"
        << std::setw(2) << std::setfill('0') << seconds << "."
        << std::setw(2) << std::setfill('0') << milliseconds;
    return oss.str();
}

int main() {
    InitWindow(600, 400, "Timer App");
    SetTargetFPS(60);

    bool timerRunning = false;
    auto startTime = std::chrono::steady_clock::now();
    std::chrono::milliseconds elapsed{0};
    std::vector<Measurement> measurements;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        time_t now = time(0);
        tm* localTime = localtime(&now);
        char buffer[64];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);
        DrawText(buffer, 20, 20, 20, BLACK);

        if (timerRunning) {
            elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now() - startTime
            );
        }

        std::string timeStr = formatTime(elapsed);
        DrawText(timeStr.c_str(), 20, 60, 30, DARKBLUE);

        Rectangle startButton = { 20, 320, 150, 40 };
        Rectangle tapButton = { 200, 320, 150, 40 };
        bool mousePressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
        Vector2 mouse = GetMousePosition();

        if (CheckCollisionPointRec(mouse, startButton) && mousePressed) {
            if (timerRunning) {
                timerRunning = false;
                // Save to file
                std::ofstream out("currentMeasurements.txt");
                for (auto& m : measurements)
                    out << m.timeString << "\n";
                out.close();
            } else {
                timerRunning = true;
                startTime = std::chrono::steady_clock::now();
                measurements.clear();
            }
        }

        if (CheckCollisionPointRec(mouse, tapButton) && mousePressed && timerRunning) {
            if (measurements.size() == 5)
                measurements.erase(measurements.begin());
            measurements.push_back({formatTime(elapsed)});
        }

        DrawRectangleRec(startButton, LIGHTGRAY);
        DrawText(timerRunning ? "Stop Timer" : "Start Timer", startButton.x + 10, startButton.y + 10, 20, BLACK);

        DrawRectangleRec(tapButton, timerRunning ? LIGHTGRAY : GRAY);
        DrawText("Tap Timer", tapButton.x + 10, tapButton.y + 10, 20, timerRunning ? BLACK : DARKGRAY);

        for (size_t i = 0; i < measurements.size(); ++i) {
            DrawText(measurements[i].timeString.c_str(), 400, 60 + 30 * i, 20, MAROON);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}