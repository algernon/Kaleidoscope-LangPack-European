# Kaleidoscope-LangPack-European

![status][st:experimental]

 [st:stable]: https://img.shields.io/badge/stable-✔-black.png?style=flat&colorA=44cc11&colorB=494e52
 [st:broken]: https://img.shields.io/badge/broken-X-black.png?style=flat&colorA=e05d44&colorB=494e52
 [st:experimental]: https://img.shields.io/badge/experimental----black.png?style=flat&colorA=dfb317&colorB=494e52

Language pack for select European languages, to be used with Kaleidoscope. This
pulign introduces a number of new key codes, which can be used to input symbols
used by selected European languages, on any operating system that support a
`Compose` key. The package has been tested under X.org and Windows with
`WinCompose`.

Supported languages: French, German, Hungarian, Polish, Swedish.

## Using the plugin

To use the plugin, one needs to include the header, and add the new keycodes to
the keymap, and add the plugin to the list of plugins used by the sketch.

## Plugin symbols

The plugin provides the `langpack::EU` object, and the following new keycodes:
(this list is currently incomplete, please see the headers for an up-to-date
one!)

### INTL_AACUTE

> Short for "a acute". The keycode results in `á`, or `Á` when shifted.

### INTL_OACUTE

> Short for "o acute". The keycode results in `ó`, or `Ó` when shifted.

### INTL_OUMLAUT

> Short for "o umlaut". The keycode results in `ö`, or `Ö` when shifted.

### INTL_ODACUTE

> Short for "o double-acute". The keycode results in `ő`, or `Ő` when shifted.

### INTL_EACUTE

> Short for "e acute". The keycode results in `é`, or `É` when shifted.

### INTL_UACUTE

> Short for "u acute". The keycode results in `ú`, or `Ú` when shifted.

### INTL_UUMLAUT

> Short for "u umlaut". The keycode results in `ü`, or `Ü` when shifted.

### INTL_UDACUTE

> Short for "u double-acute". The keycode results in `ű`, or `Ű` when shifted.

### INTL_IACUTE

> Short for "i acute". The keycode results in `í`, or `Í` when shifted.
