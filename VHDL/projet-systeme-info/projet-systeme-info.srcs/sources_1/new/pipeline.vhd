----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 04/25/2026 12:53:11 PM
-- Design Name: 
-- Module Name: pipeline - Structural
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

entity pipeline is
--  Port ( );
end pipeline;

architecture Structural of pipeline is

component ROM port(
        ADDR : in std_logic_vector( 7 downto 0);
        CLK : in std_logic;
        SORTIE : out std_logic_vector(31 downto 0)
);
end component;



signal ip : std_logic_vector(7 downto 0) := (others => '0');
signal clock : std_logic := '0';
begin

-- LES MULTIPLEXERS SERONT DES COMPOSANTS   
    mem_code : ROM port map(ADDR<=ip,);
    
    
    -- LI/LD
    
    

end Structural;
