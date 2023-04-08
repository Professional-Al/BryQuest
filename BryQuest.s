; Declare variables for storing input AND player state
input_a    db 0
input_b     db 0
input_left  db 0
input_right db 0
input_up    db 0
input_down  db 0
player_x    dw 0
player_y    dw 0
player_vx   dw 0
player_vy   dw 0
player_state db 0

; Initialize player position and velocity
player_x = 32
player_y = 32
player_vx = 0
player_vy = 0


; Main loop
loop:
    ; Read input from controller 1
    lda $4016
    sta input_a
    lda $4017
    sta input_b

    ; Update player velocity based on input
    ldy #$00
    lda input_left
    cmp #$01
    beq set_vx_left
    lda input_right
    cmp #$01
    beq set_vx_right
    sta player_vx
    jmp update_player

set_vx_left:
    sta player_vx
    jmp update_player

set_vx_right:
    lda #$01
    sta player_vx

update_player:
    ; Update player position based on velocity
    ldx player_vx
    ldy player_vy
    tax
    tay
    ldx player_x
    ldy player_y
    clc
    adc player_vx
    sta player_x
    adc player_vy
    sta player_y

    ; Update player state based on input
    lda input_up
    cmp #$01
    beq set_jumping_state
    lda input_down
    cmp #$01
    beq set_ducking_state
    sta player_state
    jmp draw_player

set_jumping_state:
    lda #$01
    sta player_state
    jmp draw_player

set_ducking_state:
    lda #$02
    sta player_state

; Draw Player Section

; Declare variables for storing player graphics and animation state
player_gfx_data  db 0
player_gfx_index dw 0
player_anim_state db 0
player_anim_frame db 0

; Draw the player sprite based on state
draw_player:
    ; Calculate the player's screen coordinates
    ldx player_x
    ldy player_y
    clc
    adc #$20 ; Adjust for horizontal centering
    sta player_screen_x
    lda player_y
    clc
    adc #$20 ; Adjust for vertical centering
    sta player_screen_y

    ; Select the appropriate graphics data based on state
    lda player_state
    cmp #$00
    beq select_standing_gfx
    cmp #$01
    beq select_jumping_gfx
    cmp #$02
    beq select_ducking_gfx

select_standing_gfx:
    lda #$00 ; Standing graphics data index
    sta player_gfx_index
    jmp draw_player_sprite

select_jumping_gfx:
    lda #$01 ; Jumping graphics data index
    sta player_gfx_index
    jmp draw_player_sprite

select_ducking_gfx:
    lda #$02 ; Ducking graphics data index
    sta player_gfx_index

draw_player_sprite:
    ; Select the appropriate frame based on animation state
    lda player_anim_state
    cmp #$00
    beq select_frame_0
    cmp #$01
