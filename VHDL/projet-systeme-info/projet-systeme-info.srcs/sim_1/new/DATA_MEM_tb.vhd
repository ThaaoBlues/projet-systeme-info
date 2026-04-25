library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity DATA_MEM_tb is
-- Les testbenches n'ont pas de ports
end DATA_MEM_tb;

architecture Behavioral of DATA_MEM_tb is

    -- Composant à tester (UUT)
    component DATA_MEM
        PORT (
            ADDR   : in std_logic_vector(7 downto 0);
            ENTREE : in std_logic_vector( 31 downto 0);
            RW     : in std_logic;
            RST    : in std_logic;
            CLK    : in std_logic;
            SORTIE : out std_logic_vector(31 downto 0)
        );
    end component;

    -- Signaux internes pour piloter l'UUT
    signal ADDR   : std_logic_vector(7 downto 0) := (others => '0');
    signal ENTREE : std_logic_vector(31 downto 0) := (others => '0');
    signal RW     : std_logic := '1'; -- Par défaut en lecture
    signal RST    : std_logic := '0';
    signal CLK    : std_logic := '0';
    signal SORTIE : std_logic_vector(31 downto 0);

    -- Définition de la période de l'horloge
    constant CLK_PERIOD : time := 10 ns;

begin

    -- Instanciation de l'Unité Sous Test (UUT)
    uut: DATA_MEM 
        PORT MAP (
            ADDR   => ADDR,
            ENTREE => ENTREE,
            RW     => RW,
            RST    => RST,
            CLK    => CLK,
            SORTIE => SORTIE
        );

    -- Génération de l'horloge
    clk_process : process
    begin
        while now < 500 ns loop -- Limite la simulation à 500ns
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
        -- 1. Reset du système
        RST <= '1';
        wait for 20 ns;
        RST <= '0';
        wait for CLK_PERIOD;

        -- 2. Écriture de données (RW = '0')
        RW     <= '0';
        ADDR   <= "00000001"; -- Adresse 1
        ENTREE <= X"AAAAAAAA";-- 0xAA
        wait for CLK_PERIOD;

        ADDR   <= "00000010"; -- Adresse 2
        ENTREE <= X"55555555"; -- 0x55
        wait for CLK_PERIOD;

        -- 3. Lecture des données (RW = '1')
        -- Lire l'adresse 1
        RW   <= '1';
        ADDR <= "00000001";
        wait for CLK_PERIOD;

        -- Lire l'adresse 2
        ADDR <= "00000010";
        wait for CLK_PERIOD;

        -- 4. Test du Reset en cours de fonctionnement
        RST <= '1';
        wait for CLK_PERIOD;
        RST <= '0';
        
        -- Vérifier après reset (doit afficher 0)
        ADDR <= "00000001";
        wait for CLK_PERIOD;

        wait;
    end process;

end Behavioral;