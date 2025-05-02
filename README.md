# Pourwar

[English](README.md) | [简体中文](README-zh-CN.md) | [Changelog](changelog.md)

Pourwar is a turn-based minigame where players fill a colorful grid map with different colors starting from the corners, similar to the "Paint Bucket Tool" in photo-editing software. The objective is to fill as more area of the map with your color as possible (Actually it's to "synchronize" these colors to yours, so that you gain control of them.) while preventing your opponent from doing the same. The game ends when one side fills half area of the map with their color and wins.

The game is designed for two players, but it can also be played against AI. The AI uses a simple algorithm to select the color that covers the most area, and it can (TODO) be adjusted to different difficulty levels.

The game is originally developed in 2018 using C++ and SDL2, as a learning project created by the author during 9th grade. It was a simple prototype and shared only on the author's social media, and seen by only a small group of friends.

The game is now being rewritten with modern C++ and Qt, transforming it into a complete game. It will be open-sourced and released on platforms like Steam.

<!-- A Gameplay Image -->