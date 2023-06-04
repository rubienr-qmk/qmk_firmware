ENCODER_MAP_ENABLE = yes

COMMAND_ENABLE     = yes # Commands for debug and configuration
CONSOLE_ENABLE     = yes # for debugging: qmk console
TERMINAL_ENABLE    = yes # command-line-like interface thorough a text editor

CAPS_WORD_ENABLE   = yes # caps lock -> caps word

# for umlaut and caps lock
# COMBO_ENABLE     = yes # umlaut
# TAP_DANCE_ENABLE = yes # umlaut

# unicode and special characters. only one at the same time: UNICODE, UNICODEMAP, UCIS
#UNICODE_ENABLE    = no  # https://docs.qmk.fm/#/feature_unicode?id=basic-unicode
#UNICODEMAP_ENABLE = no  # https://docs.qmk.fm/#/feature_unicode?id=unicode-map
UCIS_ENABLE        = yes # https://docs.qmk.fm/#/feature_unicode?id=ucis

LTO_ENABLE         = no
