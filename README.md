# HAMOOPI
 Free Fighting Game Engine

ENGLISH
-------

**HAMOOPI** is an Open Source Fighting game made in C/Allegro/SDL/Libretro. Its name is an acronym for **Half-Moon Punch**, a very Brazilian and particular way of referring to the movement of releasing a hadouken, classic movement and emblem of fighting games. This is a Brazilian engine, which is in an ALPHA and EXPERIMENTAL phase of development. This is free software, under the GPL v2 license.

Please read the documents in the [docs](docs) folder for more information on how the engine works.

### Platform Support

HAMOOPI now supports multiple platforms through its abstraction layer:
- **Allegro 4**: Original backend (default)
- **SDL2**: Modern cross-platform backend
- **Libretro**: Run in RetroArch and other libretro frontends

### Building for Libretro/RetroArch

To build as a libretro core:

```bash
make -f Makefile.libretro
```

For detailed instructions, see [README_LIBRETRO.md](README_LIBRETRO.md).

PTBR
----

**HAMOOPI** é um jogo de Luta Open Source feito em C/Allegro/SDL/Libretro. Seu nome é um acrônimo de **Half-Moon Punch** ou **Meia Lua Soco**, uma maneira muito brasileira e particular de se referir ao movimento de soltar um hadouken, movimento clássico e emblemático dos jogos de luta. Esta é uma Engine Brasileira, que está em fase ALPHA e EXPERIMENTAL de desenvolvimento. Este é um software livre, sob a licença GPL v2.

Por favor leia os documentos da pasta [docs](docs) para maiores informações sobre o funcionamento da engine.

### Suporte a Plataformas

HAMOOPI agora suporta múltiplas plataformas através de sua camada de abstração:
- **Allegro 4**: Backend original (padrão)
- **SDL2**: Backend moderno multiplataforma
- **Libretro**: Execute no RetroArch e outros frontends libretro

### Compilando para Libretro/RetroArch

Para compilar como um core libretro:

```bash
make -f Makefile.libretro
```

Para instruções detalhadas, veja [README_LIBRETRO.md](README_LIBRETRO.md).
