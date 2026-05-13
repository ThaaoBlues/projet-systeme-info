----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/11/2026 02:48:10 PM
-- Design Name: 
-- Module Name: lc_mem - Behavioral
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

entity lc_mem is
    Port ( op : in std_logic_vector (7 downto 0);
            rw_out : out std_logic);
end lc_mem;

architecture Behavioral of lc_mem is

begin
-- on doit rw que dans le code opcode commence par 101
    -- load et store
    rw_out <= '1' when op = X"A7" else 
          '0' when op = X"38" else  
          'U';                  
end Behavioral;
