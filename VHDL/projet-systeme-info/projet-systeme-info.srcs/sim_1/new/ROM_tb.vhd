library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity ROM_tb is
-- Entité vide pour un testbench
end ROM_tb;

architecture Behavioral of ROM_tb is

    -- Déclaration du composant à tester
    component ROM
        PORT (
            ADDR   : in std_logic_vector(7 downto 0);
            CLK    : in std_logic;
            SORTIE : out std_logic_vector(31 downto 0)
        );
    end component;

    -- Signaux de pilotage
    signal ADDR   : std_logic_vector(7 downto 0) := (others => '0');
    signal CLK    : std_logic := '0';
    signal SORTIE : std_logic_vector(31 downto 0);

    -- Paramètres de temps
    constant CLK_PERIOD : time := 10 ns;

begin

    -- Instanciation de la ROM
    uut: ROM 
        PORT MAP (
            ADDR   => ADDR,
            CLK    => CLK,
            SORTIE => SORTIE
        );

    -- Générateur d'horloge
    clk_process : process
    begin
        while now < 200 ns loop
            CLK <= '0';
            wait for CLK_PERIOD/2;
            CLK <= '1';
            wait for CLK_PERIOD/2;
        end loop;
        wait;
    end process;

    -- Processus de stimulus
    stim_proc: process
    begin		
        -- Attente de la stabilisation
        wait for 20 ns;

        -- Lecture de l'adresse 0
        ADDR <= std_logic_vector(to_unsigned(0, 8));
        wait for CLK_PERIOD;

        -- Lecture de l'adresse 1
        ADDR <= std_logic_vector(to_unsigned(1, 8));
        wait for CLK_PERIOD;

        -- Lecture de l'adresse 42
        ADDR <= std_logic_vector(to_unsigned(42, 8));
        wait for CLK_PERIOD;

        -- Parcours de quelques adresses dans une boucle
        for i in 10 to 15 loop
            ADDR <= std_logic_vector(to_unsigned(i, 8));
            wait for CLK_PERIOD;
        end loop;

        report "Fin de la simulation de lecture ROM";
        wait;
    end process;

end Behavioral;