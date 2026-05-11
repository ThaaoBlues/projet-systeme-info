----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/11/2026 01:24:11 PM
-- Design Name: 
-- Module Name: mux_br - Behavioral
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
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity mux_br is
    port(out_br : in std_logic_vector(7 downto 0);
    out_li_di : in std_logic_vector(7 downto 0);
    op_code : in std_logic_vector(7 downto 0);
    out_mux_br : out std_logic_vector(7 downto 0) );
end mux_br;

architecture Behavioral of mux_br is
    signal op_cool : std_logic;
begin
    op_cool <= op_code(7);
    
        -- on exclu affection et load qui n'utilise pas B comme addresse de registre
    out_mux_br <= out_br when (op_cool = '1' and (not(op_code = X"86" or op_code = X"A7"))) else out_li_di; 
    
end Behavioral;
