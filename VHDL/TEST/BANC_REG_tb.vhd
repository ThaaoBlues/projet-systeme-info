----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 04/17/2026 12:48:37 PM
-- Design Name: 
-- Module Name: BANC_REG_tb - Behavioral
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

entity BANC_tb is


end entity;

architecture bench of BANC_tb is
    
    signal ADDR_A, ADDR_B, ADDR_W : std_logic_vector(3 downto 0) := (others => '0');
    signal W : std_logic := '0';
    signal RST : std_logic := '1';
    signal CLK : std_logic := '0';
    signal DATA : std_logic_vector(7 downto 0) := (others => '0');
    signal QA, QB : std_logic_vector(7 downto 0);

begin
------------------
    bc1 : entity work.BANC
        port map (
            ADDR_A => ADDR_A, ADDR_B => ADDR_B, ADDR_W => ADDR_W,
            W => W, DATA => DATA, RST => RST, CLK => CLK,
            QA => QA, QB => QB
        );

    CLK <= not CLK after 5 ns; 


    -- write Enable
    W <= '1', '0' after 20 ns;

    -- adresses (Converties en 4 bits)
    ADDR_W <= "0001",           -- Adresse 1
              "0010" after 10 ns, -- Adresse 2
              "0000" after 20 ns; -- Adresse 0

 
    DATA <= x"7B", -- 123
            x"C8" after 10 ns; -- 200

    -- lectures
    ADDR_A <= "0001", 
              "0010" after 10 ns, 
              "0001" after 20 ns, 
              "0010" after 30 ns;
              
    ADDR_B <= "0001", 
              "0010" after 10 ns, 
              "0010" after 20 ns, 
              "0001" after 30 ns;

    -- reset
    RST <= '1', '0' after 40 ns;



    -------------------------------

    

end architecture;
