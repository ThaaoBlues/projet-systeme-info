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

architecture Behavioral of ROM is


    type mem is array(255 downto 0) of std_logic_vector(31 downto 0);
    signal rom : mem := (others => (others => '0'));
begin
    
    process(CLK)
    
    begin
    
        if CLK'Event and CLK = '1' then
        
            SORTIE <= rom(to_integer(unsigned(ADDR)));
        
        end if;
    
    
    end process;

end Behavioral;
