# cub3D

Raycaster 3D inspirado em Wolfenstein 3D, desenvolvido em C como parte do currículo da **42 Luanda**. Renderiza um labirinto em primeira pessoa a partir de um mapa `.cub`, com texturização de paredes, cores de chão/tecto e controlos de movimento.

## O que faz

- Lê um ficheiro de configuração `.cub` com texturas, cores e layout do mapa.
- Valida o mapa (fronteiras fechadas, caracteres válidos, posição do jogador única).
- Renderiza a cena em tempo real usando **raycasting** (algoritmo DDA).
- Aplica texturas diferentes para cada orientação de parede (N/S/E/W).
- Movimentação suave do jogador com `W A S D` e rotação com `← →`.

## Stack

- **Linguagem:** C (C99, `-Wall -Wextra -Werror`)
- **Gráficos:** MiniLibX (binding oficial da 42 para X11)
- **Bibliotecas internas:** `libft`, `get_next_line`

## Estrutura

```
cub3d/
├── src/
│   ├── main.c                  # Entrada, loop principal
│   ├── raycasting.c            # Algoritmo de raycasting
│   ├── raycasting/
│   │   ├── dda.c               # DDA — digital differential analyzer
│   │   └── draw_wall.c
│   ├── map.c / maps/           # Parsing e leitura de mapas
│   ├── validator/              # Validação de texturas, cores, mapa, duplicados
│   ├── events/event_hook.c     # Handlers de teclado/janela
│   └── init/ free/ utils/
├── include/                    # Headers
├── libft/                      # Biblioteca C pessoal
├── get_next_line/              # Leitura linha a linha
├── maps/                       # Mapas de teste (good/bad)
├── images/                     # Texturas XPM (paredes, porta, chão)
└── Makefile
```

## Como executar

> Requer Linux com X11 e as dependências da MiniLibX (`libx11-dev`, `libxext-dev`, `zlib1g-dev`).

```bash
# Compilar
make

# Executar com um mapa
./cub3D maps/good/valid.cub
```

### Controlos

| Tecla     | Ação                  |
| --------- | --------------------- |
| `W/A/S/D` | Mover o jogador       |
| `← / →`   | Rotacionar a câmara   |
| `ESC`     | Sair                  |

### Formato de mapa

```
NO ./images/north.xpm
SO ./images/south.xpm
WE ./images/west.xpm
EA ./images/east.xpm
F 220,100,0
C 225,30,0

1111111111
1000000001
1001N00001
1000000001
1111111111
```

## Screenshot

> A interface principal é renderizada em tempo real via MiniLibX (X11). Executar `./cub3D maps/good/valid.cub` num Linux para visualizar.
>
> ![cub3D — render in-game](docs/screenshot.png)

## Autoria

Projeto da **42 Luanda** — @rquilami, @jsoares
