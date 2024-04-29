.global assembly_function_1
assembly_function_1:
    // Save LR to the stack
    push {lr}

    // Load address of _game into R0
    ldr r0, =_game

    // Load the state field from _game into R1
    ldr r1, [r0, #0]

    // Compare the state with state_game (2)
    cmp r1, #2

    // Branch to the end if not equal
    bne end_asm1

    // Increment level if the state is state_game
    ldr r2, [r0, #12]
    add r2, r2, #1
    str r2, [r0, #12]

end_asm1:
    // Restore LR from the stack and return
    pop {lr}
    bx lr

.global assembly_function_2
assembly_function_2:
    // Save LR to the stack
    push {lr}

    // Load address of _game into R0
    ldr r0, =_game

    // Load the state field from _game into R1
    ldr r1, [r0, #0]

    // Compare the state with state_menu (1)
    cmp r1, #1

    // Branch to the end if not equal
    bne end_asm2

    // Reset the player's health if the state is state_menu
    mov r2, #10   // Set health to 10 (or any desired value)
    str r2, [r0, #20]  // Assuming player's health offset is 20

end_asm2:
    // Restore LR from the stack and return
    pop {lr}
    bx lr