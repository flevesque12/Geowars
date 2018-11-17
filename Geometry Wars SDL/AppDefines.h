#pragma once

#ifndef APPDEFINES_H
#define APPDEFINES_H

// Environment
#define WIDTH_SCREEN 800
#define HEIGHT_SCREEN 600
#define COLOR_MAX 255
#define FPS 60
#define SECOND 1000
#define SPRITES_COLUMNS 4
#define SPRITES_LINES 4
#define SPRITES_DELAY 100
#define MARGIN 10
#define MENU_ITEMS 2

// Utils
#define MULTIPLIER_FULL 1.0f
#define MULTIPLIER_QUARTER 0.25F
#define MULTIPLIER_HALF 0.5f
#define MULTIPLIER_FULL_AND_HALF 1.5f
#define MULTIPLIER_TWICE 2.0F
#define MULTIPLIER_FONT 0.05F
#define ZERO 0
#define ONE 1
#define ALPHA_MAX 255
#define RIGHT_ANGLE 90

// Player
#define JOYSTICK_DEAD_ZONE 8000
#define PLAYER_SPEED 10
#define PLAYER_MISSILE_SPEED 15
#define PLAYER_SHOOT_LIFESPAN_MULTIPLIER 1.0f
#define PLAYER_SHOOT_DELAY 140
#define PLAYER_RESPAWN_DELAY 250
#define PLAYER_INVULNERABILITY_DELAY 2000
#define ALPHA_INVULNERABLE 80
#define RUMBLE_DEATH_STRENGTH 0.6f
#define RUMBLE_DEATH_LENGTH 80
#define STARTING_LIVES 3
#define PAUSE_DELAY 500

// Sounds
#define MUSIC_HOME "Sounds/Musics/intro.ogg"
#define MUSIC_CREDITS "Sounds/Musics/credits.ogg"
#define MUSIC_LOST_GAME "Sounds/Musics/death.ogg"
#define MUSIC_LOST_GAME_BEST_SCORE "Sounds/Musics/finished.ogg"
#define MUSIC_LEVEL_01 "Sounds/Musics/level1.ogg"
#define EFFECT_MOVE_MENU "Sounds/Effects/buttonselect/3.wav"
#define EFFECT_PLAYER_LASER_01 "Sounds/Effects/lasers/7.wav"
#define EFFECT_PLAYER_SHIP_EXPLOSION "Sounds/Effects/explosions/1.wav"
#define EFFECT_PLAYER_SHIP_RESPAWN "Sounds/Effects/powerups/2.wav"

// Enemies
#define PING_PONG_HEALTH 1
#define PINT_PONG_SPEED 4
#define FOLLOWER_HEALTH 2
#define FOLLOWER_SPEED 4

#endif // !DEFINES_H
