----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 04/17/2026 02:37:42 PM
-- Design Name: 
-- Module Name: ROM - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity ROM is

    PORT (
        ADDR : in std_logic_vector( 7 downto 0);
        CLK : in std_logic;
        SORTIE : out std_logic_vector(31 downto 0)
    );
end ROM;

architecture beh of ROM is


    type mem is array(255 downto 0) of std_logic_vector(31 downto 0);
signal rom : mem := (
        -- =============================================================
        -- 1. INITIALISATION DES REGISTRES (AFC)
        -- =============================================================
        0 => x"86000A00", -- R0 <- 10 (0x0A)
        1 => x"86010500", -- R1 <- 5  (0x05)
        2 => x"86020200", -- R2 <- 2  (0x02)
        3 => x"00000000", -- NOP
        4 => x"00000000", -- NOP
        5 => x"00000000", -- NOP

        -- =============================================================
        -- 2. TESTS UAL (ADD, SOU, MUL, DIV)
        -- =============================================================
        
        -- SOUSTRACTION : R3 = R0 - R1 (10 - 5 = 5)
        6 => x"D3030001", -- Code 0xD3 | Dest R3 | Op1 R0 | Op2 R1
        7 => x"00000000", -- NOP
        8 => x"00000000", -- NOP
        9 => x"00000000", -- NOP

        -- MULTIPLICATION : R4 = R3 * R2 (5 * 2 = 10)
        10 => x"D2040302", -- Code 0xD2 | Dest R4 | Op1 R3 | Op2 R2
        11 => x"00000000", -- NOP
        12 => x"00000000", -- NOP
        13 => x"00000000", -- NOP

        -- DIVISION : R5 = R4 / R1 (10 / 5 = 2)
        14 => x"D4050401", -- Code 0xD4 | Dest R5 | Op1 R4 | Op2 R1
        15 => x"00000000", -- NOP
        16 => x"00000000", -- NOP
        17 => x"00000000", -- NOP

        -- ADDITION : R6 = R5 + R2 (2 + 2 = 4)
        18 => x"D1060502", -- Code 0xD1 | Dest R6 | Op1 R5 | Op2 R2
        19 => x"00000000", -- NOP
        20 => x"00000000", -- NOP
        21 => x"00000000", -- NOP

        -- =============================================================
        -- 3. TESTS MÉMOIRE (STORE, LOAD, COP)
        -- =============================================================

        -- STORE : M[32] <- R6 (On écrit 4 à l'adresse 0x20)
        22 => x"38200600", -- Code 0x38 | @ 0x20 | Val R6
        23 => x"00000000", -- NOP
        24 => x"00000000", -- NOP
        25 => x"00000000", -- NOP

        -- LOAD : R7 <- M[32] (R7 devrait valoir 4)
        26 => x"A7072000", -- Code 0xA7 | Dest R7 | @ 0x20
        27 => x"00000000", -- NOP
        28 => x"00000000", -- NOP
        29 => x"00000000", -- NOP

        -- COPIE : R8 <- R7
        30 => x"95080700", -- Code 0x95 | Dest R8 | Src R7
        
        others => (others => '0')
    );
begin
    
    process(CLK)
    
    begin
    
        if CLK'Event and CLK = '1' then
        
            SORTIE <= rom(to_integer(unsigned(ADDR)));
        
        end if;
    
    
    end process;

end beh;
