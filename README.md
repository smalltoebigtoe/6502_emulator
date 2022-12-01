# 6502 Emulator in C++

## Compile with testing:
```
cmake -DBUILD_TESTING=ON && make &&
```

## Run emulator or tests
```
./cmp_test
./6502_emulator
```

## Current Instruction Status
- [ ] Bitwise Instructions
- [ ] Branch Instructions
- [ ] Compare Instructions
- [ ] Flag Instructions
- [ ] Jump Instructions
- [ ] Math Instructions
- [x] Memory Instructions
- [x] Register Instructions
- [ ] Stack Instructions
- [ ] Misc. Instructions

[Reference1](https://c64os.com/post/6502instructions)

[Reference2](http://6502.org/tutorials/6502opcodes.html)

[Data sheet](http://archive.6502.org/datasheets/wdc_w65c02s_mar_2000.pdf)
