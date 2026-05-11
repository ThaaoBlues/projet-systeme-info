----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/11/2026 02:59:59 PM
-- Design Name: 
-- Module Name: mux_data_mem - Behavioral
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

entity mux_data_mem is
 Port ( 
 op : in std_logic_vector(7 downto 0);
 out_data_mem : in std_logic_vector(7 downto 0);
 out_ex_mem : in std_logic_vector(7 downto 0);
 out_b : out std_logic_vector(7 downto 0);
 );
end mux_data_mem;

architecture Behavioral of mux_data_mem is

begin


    out_b <= out_data_mem when op(5) = '1' else out_ex_mem;

end Behavioral;
