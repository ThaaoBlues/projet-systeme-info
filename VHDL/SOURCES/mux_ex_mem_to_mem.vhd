----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/11/2026 03:13:07 PM
-- Design Name: 
-- Module Name: mux_ex_mem_to_mem - Behavioral
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

entity mux_ex_mem_to_mem is
     Port ( op, ex_mem_a, ex_mem_b : in std_logic_vector(7 downto 0); out_addr : out std_logic_vector(7 downto 0));
end mux_ex_mem_to_mem;

architecture Behavioral of mux_ex_mem_to_mem is
begin
    
    -- store load     
    out_addr <= ex_mem_a when op = X"38" else ex_mem_b when op = X"A7" else "UUUUUUUU"; 
end Behavioral;
