// SystemController.h
#ifndef SYSTEMCONTROLLER_H
#define SYSTEMCONTROLLER_H

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <vector>
#include "CommandParser/CommandParser.h"
#include "../Debug/Debug.h"
#include "../Interfaces/SerialPort/SerialPort.h"
#include "../Interfaces/Wifi/Wifi.h"
#include "../Resources/Memory/Memory.h"
#include "../Resources/Storage/Storage.h"
#include "../Hardware/LedStrip/LedStrip.h"
#include "../Software/WebServer/WebServer.h"

class SystemController {
public:
    SystemController(CRGB *leds_ptr);
    void update();

    void print_help();

    // System commands
    void system_print_help();
    void system_reset();
    void system_restart();

    // Wi-Fi flows
    void                wifi_print_help();
    void                wifi_print_credentials();
    std::vector<String> wifi_get_available_networks();
    bool                wifi_connect(bool prompt_for_credentials);
    bool                wifi_read_stored_credentials(String& ssid, String& pwd);
    uint8_t             wifi_prompt_for_credentials(String& ssid, String& pwd);
    bool                wifi_join(const String& ssid, const String& password);
    bool                wifi_disconnect();
    bool                wifi_reset();

    // LED strip commands
    void led_strip_print_help();
    void led_strip_reset();
    void led_strip_set_mode(const String& args);
    void led_strip_set_rgb(const String& args);
    void led_strip_set_r(const String& args);
    void led_strip_set_g(const String& args);
    void led_strip_set_b(const String& args);
    void led_strip_set_hsv(const String& args);
    void led_strip_set_hue(const String& args);
    void led_strip_set_sat(const String& args);
    void led_strip_set_val(const String& args);
    void led_strip_set_brightness(const String& args);
    void led_strip_set_state(const String& args);
    void led_strip_turn_on();
    void led_strip_turn_off();
    void led_strip_set_length(const String& args);
    String   led_strip_get_color_hex()   const;
    uint8_t  led_strip_get_brightness()  const;
    bool     led_strip_get_state()       const;
    uint8_t   led_strip_get_mode_id()        const;

    // RAM commands
    void ram_print_help();
    void ram_status();
    void ram_free();
    void ram_watch(const String& args);

    // storage cmd
    void storage_print_help();
    void storage_set_first_startup_flag();

private:
    void define_commands();

    SerialPort      serial_port;
    Wifi            wifi;
    Memory          memory;
    Storage         storage;
    CommandParser   command_parser;
    LedStrip        led_strip;
    AsyncWebServer  server_{80};
    WebServer       web_server{*this, server_};


    // command counts
    static const size_t HELP_CMD_COUNT       = 1;
    static const size_t SYSTEM_CMD_COUNT     = 3;
    static const size_t WIFI_CMD_COUNT       = 6;
    static const size_t LED_STRIP_CMD_COUNT  = 16;
    static const size_t RAM_CMD_COUNT        = 4;
    static const size_t STORAGE_CMD_COUNT    = 2;
    static const size_t CMD_GROUP_COUNT      = 6;

    // command storage
    CommandParser::Command         help_commands[HELP_CMD_COUNT];
    CommandParser::Command         system_commands[SYSTEM_CMD_COUNT];
    CommandParser::Command         wifi_commands[WIFI_CMD_COUNT];
    CommandParser::Command         led_strip_commands[LED_STRIP_CMD_COUNT];
    CommandParser::Command         ram_commands[RAM_CMD_COUNT];
    CommandParser::Command         storage_commands[STORAGE_CMD_COUNT];
    CommandParser::CommandGroup    command_groups[CMD_GROUP_COUNT];
};

#endif // SYSTEMCONTROLLER_H
