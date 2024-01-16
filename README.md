# ViM SNAKE

While playing with ncurses to learn how it works, I found myself making a snake game :)

I did not want it to be wasted, so I decided to declare a purpose for it and share it. Its purpose is to help new Vim users to get used to Vim's navigation keys (h, j, k, l). Enjoy it :)

To compile it on Linux, run:
```shell
g++ -o vimsnake main.cpp $(pkg-config --libs ncursesw)
```
__ncurses and gcc are required.__
