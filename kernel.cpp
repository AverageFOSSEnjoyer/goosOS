void println(char* str) {
    static unsigned short* video_ptr = (unsigned short*) 0xb8000;
    for (int i = 0; str[i] != '\0'; i++) {
        video_ptr[i] = (video_ptr[i] & 0xFF00) | str[i];
    }
    video_ptr = video_ptr + 0x000a0;
}

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void call_constructors() {
    for (constructor* i = &start_ctors; i != &end_ctors; i++) {
        (*i)();
    }
}

extern "C" void kernel_main(void* multiboot_structure, unsigned int magic_number) {
    println("average GoosOS enjoyer");
    // println("                                                        _...--.");
    // println("                                        _____......----'     .'");
    // println("                                  _..-''                   .'");
    // println("                                .'                       ./");
    // println("                        _.--._.'                       .' |\"");
    // println("                     .-'                           .-.'  /");
    // println("                   .'   _.-.                     .  \\   '");
    // println("                 .'  .'   .'    _    .-.        / `./  :");
    // println("               .'  .'   .'  .--' `.  |  \\  |`. |     .'");
    // println("            _.'  .'   .' `.'       `-'   \\ / |.'   .'");
    // println("         _.'  .-'   .'     `-.            `      .'");
    // println("       .'   .'    .'          `-.._ _ _ _ .-.    :");
    // println("      /    /o _.-'               .--'   .'   \\   |");
    // println("    .'-.__..-'                  /..    .`    / .'");
    // println("  .'   . '                       /.'/.'     /  |");
    // println(" `---'                                   _.'   '");
    // println("                                       /.'    .'");
    // println("                                        /.'/.'");
    // println("                                   ___");
    // println("                               ,-""   `.");
    // println("                             ,'  _   e )`-._");
    // println("                            /  ,' `-._<.===-'");
    // println("                           /  /");
    // println("                          /  ;");
    // println("              _          /   ;");
    // println(" (`._    _.-"" ""--..__,'    |");
    // println(" <_  `-""                     \\");
    // println("  <`-                          :");
    while(1);
}