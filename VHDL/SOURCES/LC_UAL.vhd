----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/11/2026 02:08:54 PM
-- Design Name: 
-- Module Name: LC_UAL - Behavioral
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

entity LC_UAL is
    port( op : in std_logic_vector (7 downto 0);
            ctrl_out : out std_logic_vector(2 downto 0));
end LC_UAL;

architecture Behavioral of LC_UAL is
    signal op_cool : std_logic;

begin
    
    op_cool <= op(6);
           
-- Toute les instruction demandant d'utiliser une opération sont de la forme 0xCX. On a donc simplement
-- besoin de regardé le 6e bit de op.
    ctrl_out <= op(2 downto 0) when op_cool='1' else "UUU";
    
end Behavioral;
