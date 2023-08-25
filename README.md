# AROSprojekat

Program za deljenje poruka izmedju procesa koriscenjem Message Queue sistema

## Kompajliranje

Koriscenjem gcc kompajlera procesi predajnika i prijemnika mogu se kompajlirati sledecim komandama:

```
gcc predajnik.c -o predajnik -lrt
```
```
gcc prijemnik.c -o prijemnik -lrt
```

Takodje, moze se upotrebidi definisani Makefile:
```
make predajnik prijemnik
```

## Upotreba

Program se sastoji iz dva procesa, predajnika koji salje poruke u red i prijemnika koji cita poruke iz reda.

### Pozivanje predajnika:

```
./ime_procesa /ime_reda sadrzaj_poruke prioritet
```

-   **ime_procesa** - jeste naziv kompajliranog fajla. **Prema komandi iz sekcije kompajliranja "predajnik".**
-   **/ime_reda** - ovaj parametar predstavlja naziv reda koji se kreira (ako vec ne postoji) i u koji se salje poruka. **Naziv reda mora pocinjati kosom crtom "/" i ne sme biti duzi od 256 karaktera.**
-   **sadrzaj_poruke** - ovaj parametar predstavlja samu poruku koja se salje u zeljeni red. **Tekst poruke ne sme imati razmake.**
-   **prioritet** - ovaj parametar predstavlja prioritet po kome ce poruka biti procitana iz reda. **Prioritet je integer vrednost u opsegu 0-31.**

### Pozivanje prijemnika:

```
./ime_procesa /ime_reda
```

-   **ime_procesa** - jeste naziv kompajliranog fajla. **Prema komandi iz sekcije kompajliranja "prijemnik".**
-   **/ime_reda** - ovaj parametar predstavlja naziv reda iz koga se cita sledeca poruka (ako takav red postoji). **Naziv reda mora pocinjati kosom crtom "/" i ne sme biti duzi od 256 karaktera.**