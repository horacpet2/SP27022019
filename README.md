

Systém má za úkol spravovat skladové zásoby. Tím je myšleno příjem vstupních surovin jejich zpracování a oddělení procentuálního odpadu a výsledný prodej. To zároveň zahrnuje uchovávání a logování účetnictví včetně EET.

Pateřním systémem je databázový systém. Pro licencování a bezplatné použití byl zvolen databázový systém MySQL. Na tuto databázi jsou připojeni klienti. Klienti se dělí do dvou skupin:
* Pokladní systém
* Skladový systém


Pokladní systém běží na samostatném počítači opatřeném termotiskárnou a dotikovým monitorem ze kterého je možné provádět drobné prodeje. 
Skladový systém může bežet na stejném počítači jako databázový systém, ale také na jakémkoli počítači v síti. Skladový systém má za úkol spravovat skladový majetek a vytvářet faktury pro větší prodeje.

Od každého klienta může být spuštěno libovolné množství klientů na libovolném množství počítačů. To zároveň vyžaduje nutnost synchronizace přístupu k databázi.


		 |------- CASHDESK ----CASHDESK_CLIENT 1
		 | 		   |
		 |		   |---CASHDESK_CLIENT 2
		 |		   |
		 |		   |---CASHDESK_CLIENT 3
		 |
DATABASE |
		 |
		 |
		 |
		 |
		 |
		 |------- STOCK -----STOCK_CLIENT 1
			        |
			        |----STOCK_CLIENT 2
			        |
			        |----STOCK_CLIENT 3





Architekturua je rozdělena do čtiř částí (vrstev):
* TRANSVRSTVA - společná vrstva která obsahuje kód viditelný ve šech vrstvách
* CONTROLER - logika programu
* VIEW - prezentační vrstva s grafickým uživatelským rozhraním
* MAIN -  hlavní víkonné vlákno programu


moduly alarm buffer, alarm widget a alarm tvoří architekturu model-view-controler kde alarm buffer je model, alarm widget je view a alarm tvoří controler.


běhové knihovny GTK pro windows:
https://github.com/tschoonj/GTK-for-Windows-Runtime-Environment-Installer


Rezervované IP adresy:

Pokladna: 192.168.1.10
Správa skladu (databáze): 192.168.1.11


Důležité je aby se nějakou dobu používaly oba systémy (nový i starý), nový systém poběží nějakou dobu v testovacím režimu a v případě chyby se může získat záloha ze starého systému. Po odladění všech nedostatků se bude moct přejít naplno na nový systém

Požadavkem je aby bylo možné obilí a mouku dynamicky menedžovat. Občas je přivezeno obilí, které jde pouze na semletí. To znamená že je třeba zaznamenat přesné množství obilí které ve vlastnictví jiného člověka
Řešením jsou virtuální sila. Virtuální sila jsou skladovací jednotky s obilím a semletou moukou. Jedná se o obdobu fyzických sil ve kterých se skladuje obilí a semletá mouka, díky tomu je snazší se v tomto orientovat.
Každé silo má datové atributy: ID, jméno sila, druh obilí/mouky/otrub, produkt (obilí/kouka/otruby) , množství, poznámka
Tato sila se nachízejí v jedné databázové tabulce do které lze dynamicky přidávat nebo odebírat virtuální sila.
Každé silo má příznak, který určuje co se v něm nachízí a podle toho nabízí určité funkce.
- semlýt (obilí)
- napytlovat (obilí/mouka, otruby) (kolik pytlů s jakou váhou)
- vyhodit (obilí/mouka/otruby)
- prodat (obilí/mouka/otruby)
- přesunout (obilí/mouka/otruby)

v programu je nastaven seznam produktů se kterými je ve mlýně manypulováno, každé silo tak má nastaveno co je uvnitř, a mezi jednotlivými sili lze obsah přesouvat ale pouze v případě, že je uvnitř obsah stejný.

Při pytlování se zadá kolik pytlů se napytlovalo s jakou váhou, automaticky se odečte dané množství ze sila a počet pytlů se uloží do databázové tabulky pro pokladní systém

Jednotlivé transakce ať z pokladního systému tak přes faktury se ukládají do databázové tabulky s transakcemi. Tam je zároveň označeno zda byla transakce provedena přes fakturu nebo přes pokladní systém s EET. Z této databáze bude možné znovu zrekonstruovat účtekny s údaji EET pro účetnictví, takže není nutné vždy tisknout účtenku dvakrát (vícekrát).

Fakturou lze brát produkty jak z virtuálních sil tak ze skladu s pytli.


Je třeba zajistit, aby se při načítání položek do manualního vstupu nahrály všechny položky korektně (díry v intervalech ID) -> je třeba udržet ID konzistentní, to je třeba zajistit v programu pro správu majetku

databázové tabulky:
stock
virtual_silo
transactions
transactions_for_send - transakce pro odeslání do EET v případě odpojení sítě (provedení pro možnost více připojených podkladních systémů, nutnost lokálního záznamu)




** postgres **

výpis všech databázových tabulek v dané databázi:  \dt
výpis všech databází v systému: \l
přepnutí do dané databázové tabulky \c jmeno_tabulky
výpis jmen a datových typů jednotlivých sloupců tabulky: \d+ jmeno_tabulky
vymazání database: DROP DATABASE jmeno_databaze;
vytvoření databáze: CREATE DATABASE jméno_databáze;
vytvoření databázové tabulky: CREATE TABLE jmeno_databaze(formát tabulky);

(http://127.0.0.1:56642/browser/)

pro nastavení připojení ke vzdáleným počítačům je třeba připsat do konfiguračního souboru: PostgreSQL/<Verze>Data/pg_hba.conf

host	all		all		192.168.1.11/32	md5

v souboru postgresql.conf
je třeba nastavit listen_address = '*'

vytvoří tabulku pro sklad: CREATE TABLE stock(ID int, itemName varchar(255), itemShorcutName varchar(255), quantity int, tax float, price float);
vloží záznam do tabulky stock: INSERT INTO stock VALUES(1, 'Žitná mouka 5Kg', 'Žit m 5Kg', 100, 1.15, 55);
vrátí počet záznamů v tabulce stock SELECT COUNT(*) FROM stock;
UPDATE stock SET quantity=xxx WHERE ID=1;


** TODO **

* upravit propojení value_widgetu pro zobrazování ceny na obrazovce objednávky a na obrazovce dokončení objednávky
* pozměnit vyčítání dat do karty manuální vstup, komunikace je pomalá a zpomaluje se celý systém
* vytvořit kartu s potvrzením odeslání dat do systému EET
* knihovna EET 
* vytvořit kartu v grafickém rozhraní pro práci se systémovým nastavením
* napojit systémové nastavení

** DONE **

* pozměnit propojení pro vyčítání skladových položek do karty manuálního vstupu pro zrychlení programu
* napojit vlákno pro sledování spojení se serverem
* napojit chybový log do chybového bufferu
* napojit chybový buffer
* napojit systémový log 
* napojení databáze
* vytvořit strukturu databáze
* generování kódu pro tisk účtenky
* odesílání kódu účtenky do tiskárny
* vytvořit rozhraní pro vyčítání parametrů položky objednávky z databáze (v controleru)	
* zaokrouhlit cenu objednávky
* napojit kalulátor na počítání s cenou objednávky
* napojit cenu objednávky do obrazovky s dokončením objednávky
* napojit na tlačítko doknčit v obrazovce pro dokončení objednávky příkaz na vyčištění objednákového seznamu
* napojit inkrementaci na tlačítku v obrazovce objednávek
* napojit dekrementaci na tlačítko v obrazovce objednávek
* napojit vyčištění objednávky na tlačítko v obrazovce objednávek
* vytvořit funkcionalitu na označení položek v seznamu
* přidat skrolování do seznamu
* napojit výslednou cenu do obrazovky s objednávkou




Špaldová celozrnná 26kč/kg bez dph
otruby jedlé (místo 50 je 40kg) 5kč/kg bez dph
otruby krmné pouze 40kg 2.50kč/kg bez dph


na účtenku přidat webovou adresu, ič, dič, datum uzkutečnění zdanitelného plnění




** BUGS **

BUG 001 - pád programu bez udání příčiny při přechodu na obrazovku platby - opraveno, chybné načítání parametrů pro order_item
chyba se objevuje při stisknutí tlačítka Zaplatit. Ve volané obslužné funkci se vykonává generování kódu pro tiskánu, které bylo v nedávné době vytvořeno a implementováno, od této doby byl dvakrát zaznamenám pád programu. Chyba se pravděpodobně nachází uvnitř funkce  controler_build_bill.
Tato funkce pracuje s neuplnými daty, protože databáze ještě není napojena, je možné, že k pádu dojde z důvodu chybného přístupu k neúplným datům, 
Chyba se bude řešit až po napojení databáze a kompletních datech ve struktuře order_list, funkce je do té doby zakomentována


BUG 002 - pokud se zadají dvě položky se stejným ID program spadne

BUG 003 - při spuštění programu se aktivuje error chyba připojení k serverovému počítači, ale po vyresetování zmizí a už se neobjeví
- opraveno - chyba byla způsobena chybou při hlášení chyb, spojení se neaktivovalo kvůli chybné konfigurace adresy a chyba se po vyresetování již nenahlásila


















