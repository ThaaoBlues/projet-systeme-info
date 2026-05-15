----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/11/2026 02:22:56 PM
-- Design Name: 
-- Module Name: mux_ual - Behavioral
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

entity mux_ual is
     Port ( out_ual : in std_logic_vector(7 downto 0);
    out_di_ex : in std_logic_vector(7 downto 0);
    op_code : in std_logic_vector(7 downto 0);
    out_mux_ual : out std_logic_vector(7 downto 0) );
end mux_ual;

architecture Behavioral of mux_ual is
    signal op_cool : std_logic;
begin
   op_cool <= op_code(6);
   out_mux_ual <= out_ual when (op_cool = '1') else out_di_ex; 


end Behavioral;
