#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void wczytaj(struct plik_grafika *obrazy, int *ile_obrazow, struct plik_grafika *obraz_aktywny);
void alokuj_2D(int ***tablica, int wysokosc, int szerokosc);
void zwolnij_2D(int ***tablica, int wysokosc, int szerokosc);
void reallokuj_1D(int **obraz, int *ile_obrazow);
void zapisz(struct plik_grafika *obraz_aktywny, int *ile_obrazow, struct plik_grafika **obrazy);
void wybierz_aktywny(struct plik_grafika *obrazy, struct plik_grafika **obraz_aktywny, int *ile_obrazow);
void wyswietl_wczytane_obrazy(struct plik_grafika *obrazy, int *ile_obrazow);
void usun_obraz(struct plik_grafika **obrazy, int *ile_obrazow);
void obrot(struct plik_grafika *obraz_aktywny);
void obrot_x(struct plik_grafika *obraz_aktywny);
void obrot_y(struct plik_grafika *obraz_aktywny);
void histogram(struct plik_grafika *obraz_aktywny);
void progowanie(struct plik_grafika *obraz_aktywny);
void negatyw(struct plik_grafika *obraz_aktywny);
void zaklocenie(struct plik_grafika *obraz_aktywny);
void filtr_medianowy(struct plik_grafika **obraz_aktywny);
void filtr_Gaussa(struct plik_grafika **obraz_aktywny);
int wczytaj_int(int * liczba);
void idioto_ochrona(int * liczba);



struct plik_grafika                   //struktura obrazu pgm
{
	char *nazwa[50];
	char standard[2];
	int szerokosc;
	int wysokosc;
	int **tablica;
	int max_szarosc;
};

int main()
{

	int a, b, c;                                              // zmienne pomocnicze do funkcji switch
	int *ile_obrazow;
	struct plik_grafika *obrazy;
	ile_obrazow = (int*)malloc(1 * sizeof(int));
	obrazy = (struct plik_grafika*)malloc(1 * sizeof(struct plik_grafika));
	*ile_obrazow = 0;
	struct plik_grafika *obraz_aktywny;          
	obraz_aktywny = (struct plik_grafika*)malloc(1 * sizeof(struct plik_grafika));
	srand(time(NULL));

	printf("Menu uzytkownika:\n   1. Wczytaj obraz.\n   2. Zapisz obraz.\n   3. Wybierz obraz na ktorym chcesz dokonac zmian.\n   4. Przetwarzaj obraz.\n   5. Wyswietl liste wczytanych obrazow.\n   6. Usun obraz z listy.\n   7. Zakoncz. \n");
	do
	{
		if (*ile_obrazow != 0)
		{
			system("cls");
			printf("Menu uzytkownika:\n   1. Wczytaj obraz.\n   2. Zapisz obraz.\n   3. Wybierz obraz na ktorym chcesz dokonac zmian.\n   4. Przetwarzaj obraz.\n   5. Wyswietl liste wczytanych obrazow.\n   6. Usun obraz z listy.\n   7. Zakoncz. \n");
		}
		idioto_ochrona(&a);
			
		switch (a)
		{
		case 1:
			*ile_obrazow += 1;
			reallokuj_1D(&obrazy, ile_obrazow);
			wczytaj(obrazy, ile_obrazow, obraz_aktywny);
			break;
		case 2:
			if (*ile_obrazow == 0)
			{
				printf("Brak obrazu do zapisu. Najpierw wczytaj obraz.\n");
				break;
			}
			*ile_obrazow += 1;
			reallokuj_1D(&obrazy, ile_obrazow);
			zapisz(obraz_aktywny, ile_obrazow, &obrazy);
			(obrazy)[*ile_obrazow - 1] = *obraz_aktywny;
			printf("Obraz zapisano.\n\n\n");
			break;
		case 3:
			if (*ile_obrazow == 0)
			{
				printf("Brak obrazow. Najpierw wczytaj obraz.\n");
				break;
			}
			wybierz_aktywny(obrazy, &obraz_aktywny, ile_obrazow);
			printf("Obraz aktywny to: %s\n\n", *(*obraz_aktywny).nazwa);
			break;
		case 4:
			if (*ile_obrazow == 0)
			{
				printf("Brak obrazu do przetworzenia. Najpierw wczytaj obraz.\n");
				break;
			}
			do
			{
				system("cls");
				if (a == 1)
				{
					printf("Obraz zostal przetworzony. W celu zapisania zmian opusc przetwarzanie obrazu i wybierz opcje 'zapisz' z menu uzytkownika\n\n");
				}
				printf("Obraz aktywny to: %s\n\n   1. Obroc obraz o 90 stopni.\n   2. Obroc obraz wzgledem osi X.\n   3. Obroc obraz wzgledem osi Y.\n   4. Wygeneruj histogram i zapisz plik do excel.\n   5. Progowanie.\n   6. Negatyw.\n   7. Szum pieprz-sol.\n   8. Filtr.\n   9. Koniec przetwarzania.\n", *(*obraz_aktywny).nazwa);
				idioto_ochrona(&b);
				switch (b)
				{
				case 1:
					system("cls");
					printf("W ktora strone chcesz obrocic obraz:\n   1. w prawo\n   2. w lewo.\n");
					idioto_ochrona(&c);
					switch (c)
					{
					case 1:
						obrot(obraz_aktywny);
						break;
					case 2:
						obrot(obraz_aktywny);
						obrot_y(obraz_aktywny);
						obrot_x(obraz_aktywny);
						break;
					default:
						printf("Wybierz jeden z dostepnych numerow.");
					}
					a = 1;
					break;
				case 2:
					obrot_x(obraz_aktywny);
					a = 1;
					break;
				case 3:
					obrot_y(obraz_aktywny);
					a = 1;
					break;
				case 4:
					histogram(obraz_aktywny);
					a = 1;
					break;
				case 5:
					progowanie(obraz_aktywny);
					a = 1;
					break;
				case 6:
					negatyw(obraz_aktywny);
					a = 1;
					break;
				case 7:
					zaklocenie(obraz_aktywny);
					a = 1;
					break;
				case 8:
					system("cls");
					printf("Wybierz filtr:\n   1. medianowy\n   2. Gaussa.\n");
					idioto_ochrona(&c);
					switch (c)
					{
					case 1: 
						filtr_medianowy(&obraz_aktywny);
						break;
					case 2:
						filtr_Gaussa(&obraz_aktywny);
						break;
					default:
						printf("Wybierz jeden z dostepnych numerow.");
					}
					a = 1;
					break;
				case 9:
					break;
				default:
					b = 10;
					printf("Wybierz liczbe z menu uzytkownika.\n");
					break;
				}
			} while (b == 1 || b == 2 || b == 3 || b == 4 || b == 5 || b == 6 || b == 7 || b == 8 || b == 10);

			break;
		case 5:
			if (*ile_obrazow == 0)
			{
				printf("Brak obrazow. \n");
				break;
			}
			wyswietl_wczytane_obrazy(obrazy, ile_obrazow);
			system("PAUSE");
			break;			
		case 6:
			if (*ile_obrazow == 0)
			{
				printf("Brak obrazow. Najpierw wczytaj obraz. \n");
				break;
			}
			usun_obraz(&obrazy, ile_obrazow);
			*obraz_aktywny = obrazy[*ile_obrazow - 1];
			break;
		case 7:
			free(obrazy);
			free(ile_obrazow);
			free(obraz_aktywny);
			exit(0);
		default:
			a = 8;
			printf("Wybierz liczbe z menu uzytkownika.\n");
			break;
			}

	} while (a == 1 || a == 2 || a == 3 || a == 4 || a == 5 || a == 6 || a == 8);

	return 0;
}

void alokuj_2D(int ***tablica, int wysokosc, int szerokosc)                   // dynamiczna alokacja pamieci dla tablicy dwuwymiarowej
{
	int i = 0, j = 0;
	*tablica = malloc( wysokosc * sizeof(**tablica));

	if (*tablica != NULL)
	{
		for (i = 0; i < wysokosc; i++)
		{
			(*tablica)[i] = malloc(szerokosc * sizeof(int));
			
			if ((*tablica)[i] == NULL)
			{
				printf("Blad alokacji.");                                     // zwolnienie wczesniej zaalokowanej pamieci w przypadku niepowodzenia
				for (j = 0; j < wysokosc; j++)
				{
					free((*tablica)[i]);
				}
				free(*tablica);
			}

		}
	}
	else
	{
		printf("Blad alokacji.");
		free(*tablica);
	}
}

void zwolnij_2D(int ***tablica, int wysokosc, int szerokosc)               // funkcja zwalniaj¹ca pamiec tablicy dwuwymiarowej
{
	int i = 0, j = 0;

	for (i = 0; i < wysokosc; i++)
	{
		free((*tablica)[i]);
	}
	free(*tablica);
}

void reallokuj_1D(int **obraz, int *ile_obrazow)                             // funkcja powiekszajaca tablice obrazow o 1 przy dodawaniu lub zapisywaniu nowego obrazu
{
	int *tab_proba = NULL;
	tab_proba = realloc(*obraz, (*ile_obrazow ) * sizeof(struct plik_grafika));
	if (tab_proba != NULL)
	{
		*obraz = tab_proba;
	}
	else
	{
		printf("Blad realokacji.");
		free(tab_proba);
	}
}


void wczytaj(struct plik_grafika *obrazy, int *ile_obrazow, struct plik_grafika *obraz_aktywny)
	{
		char nazwa_pliku[50];
		char *nazwa_obrazu;
		char standard_pliku[3];				                    	  
		int wysokosc = 0;
		int szerokosc = 0;
		int max_szarosc = 0;
		int i = 0;
		int j = 0;
		int **tablica;
		FILE* plik;

		nazwa_obrazu = malloc(50 * sizeof(char));
		obrazy = (obrazy + (*ile_obrazow) - 1);							     // wczytywanie obrazu do odpowiedniego adresu
		do
		{
			printf("Podaj nazwe %d. obrazu : ", *ile_obrazow);
			scanf("%s", nazwa_pliku);
			printf("\n");

			strcat(nazwa_pliku, ".pgm");                                    // dopisanie rozszerzenia pgm do nazwy pliku
			strcpy(nazwa_obrazu, nazwa_pliku);
			*(*obrazy).nazwa = nazwa_obrazu;

			plik = fopen(nazwa_obrazu, "r");

			if (plik == NULL)                                               // w przypadku niepowodzenia otwarcia pliku/ braku danego pliku
			{
				printf("Nie udalo sie odczytac pliku %s. Najprawdopodobniej w folderze nie ma obrazu o podanej nazwie. Sprobuj ponownie.\n", nazwa_obrazu);
			}
			else
			{
				fscanf(plik, "%s\n", standard_pliku);
				if (standard_pliku[1] == '2')								//sprawdzam czy wczytano dobry standard, nie potrzeba ochrony pzed kom bo stndard zawsze jest pierwszy
				{
					(*obrazy).standard[0] = 'P';
					(*obrazy).standard[1] = '2';
				}
				else if (standard_pliku[1] == '5')
				{
					(*obrazy).standard[0] = 'P';
					(*obrazy).standard[1] = '5';
				}
				else
				{
					printf("Bledny standard pliku.");
				}

				do {
					i = fscanf(plik, "%d ", &szerokosc);                // ignorowanie komentarzy, przesuniecie kursora o jeden dalej jezeli wczytany znak nie jest liczba
					if (i == 0)
					{
						fseek(plik, 1, SEEK_CUR);
					}
				} while (i != 1);

				do {
					i = fscanf(plik, "%d\n", &wysokosc);
					if (i == 0)
					{
						fseek(plik, 1, SEEK_CUR);
					}
				} while (i != 1);

				(*obrazy).wysokosc = wysokosc;
				(*obrazy).szerokosc = szerokosc;

				do {
					i = fscanf(plik, "%d\n", &max_szarosc);
					if (i == 0)
					{
						fseek(plik, 1, SEEK_CUR);
					}
				} while (i != 1);

				(*obrazy).max_szarosc = max_szarosc;


				alokuj_2D(&tablica, wysokosc, szerokosc);
				alokuj_2D(&(*obrazy).tablica, (*obrazy).wysokosc, (*obrazy).szerokosc);

				for (i = 0; i < wysokosc; i++)                                                            //uzupelnienie tablicy pikseli
				{
					for (j = 0; j < szerokosc; j++)
					{
						while (fscanf(plik, "%d\n", &tablica[i][j]) != 1)
						{
							fseek(plik, 1, SEEK_CUR);
						}
						(*obrazy).tablica[i][j] = tablica[i][j];
					}
				}
			}

		} while (plik == NULL);
 
		*obraz_aktywny = *obrazy;                                                                   // ostatni wczytany obraz automatycznie staje sie obrazem aktynym
		fclose(plik);
		zwolnij_2D(&tablica, wysokosc, szerokosc);
}


void zapisz(struct plik_grafika *obraz_aktywny,int *ile_obrazow, struct plik_grafika **obrazy)
{
	int i = 0;
	int j = 0;
	FILE* plik;
	char nazwa_pliku[50];	
	char *nazwa_obrazu;

	nazwa_obrazu = malloc(50 * sizeof(char));
	do
	{
		printf("Uwaga! Podanie nazwy obrazu juz istniejacej w folderze spowoduje trwale usuniecie poprzedniego obrazu \ni zapisanie obecnego w jego miejsce.\nPodaj nazwe obrazu: ");
		scanf("%s", nazwa_pliku);
		printf("\n");
		strcat(nazwa_pliku, ".pgm");                                                          // dodanie ".pgm" do nazwy zapisywanego pliku
		strcpy(nazwa_obrazu, nazwa_pliku);

		plik = fopen(nazwa_obrazu, "w");
		if (plik == NULL)
		{
			printf("Blad zapisu. Sprobuj ponownie.\n");
		}
		else                                                                                                   //zapisanie do pliku obrazu pgm
		{
			*(*obraz_aktywny).nazwa = nazwa_obrazu;
			fprintf(plik, "%c%c\n", (*obraz_aktywny).standard[0], (*obraz_aktywny).standard[1]);
			fprintf(plik, "%d %d\n%d\n", (*obraz_aktywny).szerokosc, (*obraz_aktywny).wysokosc, (*obraz_aktywny).max_szarosc);

			for (i = 0; i < (*obraz_aktywny).wysokosc; i++)
			{
				for (j = 0; j < (*obraz_aktywny).szerokosc; j++)
				{
					fprintf(plik, "%d ", (*obraz_aktywny).tablica[i][j]);
				}
				fprintf(plik, "\n");
			}
		}
	} while (plik == NULL);
	fclose(plik);
}


void wybierz_aktywny(struct plik_grafika *obrazy, struct plik_grafika **obraz_aktywny, int *ile_obrazow)
{
	int a, b;

	printf("Czy chcesz najpierw wyswietlic liste dostepnych obrazow? \n   1. TAK\n   2. NIE\n");
	idioto_ochrona(&a);
	
	switch (a)
	{
	case 1:
		wyswietl_wczytane_obrazy(obrazy, ile_obrazow);
	case 2:
		printf("\nPodaj numer obrazu na ktorym chcesz dokonac zmian: ");
		idioto_ochrona(&b);

		while (b < 1 || b > *ile_obrazow)
		{
			printf("Obraz o danym numerze nie istnieje. Podaj numer obrazu ktory jest dostepny: ");
			idioto_ochrona(&b);
		}

		**obraz_aktywny = (obrazy)[b - 1];                                                                   // przypisanie strukturze obrazu aktywnego wybranego obrazu z listy wczytanych
		break;
	default:
		printf("Wybierz jeden z dostepnych numerow.\n");
		break;
	}
}


void wyswietl_wczytane_obrazy(struct plik_grafika *obrazy, int *ile_obrazow) 
{
	int i = 0;
	printf("Lista wczytanych obrazow:\n");

	for (i = 0; i < *ile_obrazow ; i++)
	{
		printf("   %d. %s\n", i + 1, *obrazy[i].nazwa);
	}
}


void usun_obraz(struct plik_grafika **obrazy, int *ile_obrazow)
{
	int a, b, i;
	int *realokacja_proba = NULL;
	printf("Czy chcesz najpierw wyswietlic liste wczytanych obrazow? \n   1. TAK\n   2. NIE\n");
	idioto_ochrona(&a);

	switch (a)
	{
	case 1:
		wyswietl_wczytane_obrazy(*obrazy, ile_obrazow);
	case 2:
		printf("\nPodaj numer obrazu ktory chcesz usunac: ");
		idioto_ochrona(&b);

		while (b < 1 || b > *ile_obrazow)
		{
			printf("\nObraz o danym numerze nie istnieje. Podaj numer obrazu ktory chcesz usunac: ");
			idioto_ochrona(&b);
		}

		if ((*ile_obrazow) == b)                                          // w przypadku usuniecia ostatnio wczytanego obrazu
		{
			printf("\nObraz nr %d usunieto\n", b);
		}
		else                                                              // w przypadku usuniecia innego obrazu - zamiana miejsc obrazow, przesuniecie kazdego za usunietym a jeden "w przod"
		{
			for (i = 0; i < (*ile_obrazow - b); i++)
			{
				*(*obrazy + (b - 1 + i)) = *(*obrazy + (b + i));
			}
			printf("\nObraz nr %d usunieto\n", b);
		}

		*ile_obrazow = *ile_obrazow - 1;
		
		if (*ile_obrazow != 0)
		{
			realokacja_proba = realloc(*obrazy, (*ile_obrazow) * sizeof(struct plik_grafika));               // usuniecie ostatniego obrazu
			if (realokacja_proba == NULL)
			{
				printf("Relokacja nie powiodla sie.\n");
			}
			else
			{
				*obrazy = realokacja_proba;
			}
			system("PAUSE");
		}
		else                                                                                   // relokacja nie powiedzie sie w przypadku gdy chcemy zarezerwowac zero miejsca dla obrazow
		{
			system("cls");
			printf("Brak obrazow. \n");
			printf("Menu uzytkownika:\n   1. Wczytaj obraz.\n   2. Zapisz obraz.\n   3. Wybierz obraz na ktorym chcesz dokonac zmian.\n   4. Przetwarzaj obraz.\n   5. Wyswietl liste wczytanych obrazow.\n   6. Usun obraz z listy.\n   7. Zakoncz. \n");
		}
		break;
	default:
		printf("Wybierz jeden z dostepnych numerow.\n");
		break;
	}
}


void obrot(struct plik_grafika *obraz_aktywny)
{
	int i, j;
	int **tab_pomocnicza = (*obraz_aktywny).tablica;

	i = (*obraz_aktywny).wysokosc;                                            // zamiana wartosci wysokosci i szerokosci obrazu aktywnego
	(*obraz_aktywny).wysokosc = (*obraz_aktywny).szerokosc;
	(*obraz_aktywny).szerokosc = i;

	alokuj_2D(&(*obraz_aktywny).tablica, (*obraz_aktywny).wysokosc, (*obraz_aktywny).szerokosc);

	for (i = 0; i < ((*obraz_aktywny).wysokosc); i++)                        // odpowiednie przepisanie pikseli z tablicy pomocniczej - poprzedniej tablicy pikselow obrazu aktywnego
	{
		for (j = 0; j < ((*obraz_aktywny).szerokosc); j++)
		{
			(*obraz_aktywny).tablica[i][j]= tab_pomocnicza[(*obraz_aktywny).szerokosc - j - 1][i];
		}
	}

	free(tab_pomocnicza);
}


void obrot_x(struct plik_grafika *obraz_aktywny)
{
	int i, j;
	int**tab_pomocnicza;
	alokuj_2D(&tab_pomocnicza, (*obraz_aktywny).wysokosc, (*obraz_aktywny).szerokosc);

	for (i = 0; i < ((*obraz_aktywny).wysokosc); i++)
	{
		for (j = 0; j < ((*obraz_aktywny).szerokosc); j++)
		{
			tab_pomocnicza[i][j] = (*obraz_aktywny).tablica[(*obraz_aktywny).wysokosc - i - 1][j];
		}
	}

	for (i = 0; i < ((*obraz_aktywny).wysokosc); i++)
	{
		for (j = 0; j < ((*obraz_aktywny).szerokosc); j++)
		{
			(*obraz_aktywny).tablica[i][j] = tab_pomocnicza[i][j];
		}
	}
}


void obrot_y(struct plik_grafika *obraz_aktywny)
{
	int i, j;
	int**tab_pomocnicza;
	alokuj_2D(&tab_pomocnicza, (*obraz_aktywny).wysokosc, (*obraz_aktywny).szerokosc);

	for (i = 0; i < ((*obraz_aktywny).wysokosc); i++)
	{
		for (j = 0; j < ((*obraz_aktywny).szerokosc); j++)
		{
			tab_pomocnicza[i][j] = (*obraz_aktywny).tablica[i][(*obraz_aktywny).szerokosc - j - 1];
		}
	}

	for (i = 0; i < ((*obraz_aktywny).wysokosc); i++)
	{
		for (j = 0; j < ((*obraz_aktywny).szerokosc); j++)
		{
			(*obraz_aktywny).tablica[i][j] = tab_pomocnicza[i][j];
		}
	}
}


void histogram(struct plik_grafika *obraz_aktywny)
{
	int i,j;
	int *tab_pomocnicza = NULL;
	char nazwa_pliku[50];

	FILE* plik;

	tab_pomocnicza = malloc(((*obraz_aktywny).max_szarosc + 1) * sizeof(int));                   // +1 bo 0 tez jest odcieniem


	for (i = 0; i <= (*obraz_aktywny).max_szarosc; i++)                                     // wyzerowanie tablicy dla kazdego odcienia
	{
		tab_pomocnicza[i] = 0;
	}

	for (i = 0; i < ((*obraz_aktywny).wysokosc); i++)                                      //dodawanie koljnych pikseli tego samego odcienia
	{
		for (j = 0; j < ((*obraz_aktywny).szerokosc); j++)
		{
			tab_pomocnicza[(*obraz_aktywny).tablica[i][j]] += 1;
		}
	}

	printf("Podaj nazwe pliku: ");
	scanf("%s", nazwa_pliku);
	printf("\n");
	strcat(nazwa_pliku, ".csv");

	plik = fopen(nazwa_pliku, "w");
	if (plik == NULL)
	{
		printf("blad zapisu");
		free(tab_pomocnicza);
	}

	else
	{
		for (i = 0; i <= (*obraz_aktywny).max_szarosc; i++)                        // wprowadzenie do excela w pierwszym rzedzie tabeli odcieni szarego od 0 do maksymalnego danego brazu
		{
			fprintf(plik, "%d;",i);
		}
		fprintf(plik, "\n");
		for (i = 0; i <= (*obraz_aktywny).max_szarosc; i++)                         // wprowadzenie do excela w drugim rzedzie ilosci wystapienia piksela danego odcieniu
		{
			fprintf(plik, "%d;", tab_pomocnicza[i]);
		}

	}
	fclose(plik);

	free(tab_pomocnicza);
}


void progowanie(struct plik_grafika *obraz_aktywny)
{
	int a = 0, i = 0, j = 0;

	do
	{
		printf("Podaj prog od 0 do %d: ", (*obraz_aktywny).max_szarosc);
		idioto_ochrona(&a);
	} while (a < 0 || a > (*obraz_aktywny).max_szarosc);

	for (i = 0; i < ((*obraz_aktywny).wysokosc); i++)
	{
		for (j = 0; j < ((*obraz_aktywny).szerokosc); j++)
		{
			if ((*obraz_aktywny).tablica[i][j] < a)                 // przypisanie 0 pikselom mniejszym niz zadany prog a 1 wiekszym
			{
				(*obraz_aktywny).tablica[i][j] = 0;
			}
			else
			{
				(*obraz_aktywny).tablica[i][j] = 1;
			}
		}
	}
	(*obraz_aktywny).max_szarosc = 1;
}


void negatyw(struct plik_grafika *obraz_aktywny)
{
	int i = 0, j = 0;
	int nowy = 0;

	for (i = 0; i < ((*obraz_aktywny).wysokosc); i++)
	{
		for (j = 0; j < ((*obraz_aktywny).szerokosc); j++)
		{
			nowy = (*obraz_aktywny).max_szarosc - (*obraz_aktywny).tablica[i][j];               // odwrocenie odcieni
			(*obraz_aktywny).tablica[i][j] = nowy;
		}
	}
}


void zaklocenie(struct plik_grafika *obraz_aktywny)
{
	int i = 0, j = 0, a = 0, b = 0, c = 0, procent_zaszumienia = 0, liczba_pikseli = 0, liczba_zaszumionych_pikseli = 0, liczba_rzeczywiscie_zaszumionych = 0;

	printf("Podaj procent zaszumienia: ");
	idioto_ochrona(&procent_zaszumienia);

	while (procent_zaszumienia < 0 || procent_zaszumienia > 100)
	{
		printf("Podaj procent zaszumienia z zakresu od 0 do 100: ");
		idioto_ochrona(&procent_zaszumienia);
	}

	liczba_pikseli = ((*obraz_aktywny).wysokosc) * ((*obraz_aktywny).szerokosc);
	liczba_zaszumionych_pikseli = (procent_zaszumienia * liczba_pikseli) / 100;

	do
	{
		liczba_zaszumionych_pikseli -= liczba_rzeczywiscie_zaszumionych;
		for (i = 0; i < liczba_zaszumionych_pikseli; i++)
		{
			a = rand() % (*obraz_aktywny).wysokosc;
			b = rand() % (*obraz_aktywny).szerokosc;

			c = rand() % 2;

			if (c == 1)
			{
				(*obraz_aktywny).tablica[a][b] = 0;
			}
			else
			{
				(*obraz_aktywny).tablica[a][b] = (*obraz_aktywny).max_szarosc;
			}
		}

		for (i = 0; i < ((*obraz_aktywny).wysokosc); i++)
		{
			for (j = 0; j < ((*obraz_aktywny).szerokosc); j++)
			{
				if ((*obraz_aktywny).tablica[i][j] == 0 || (*obraz_aktywny).tablica[i][j] == (*obraz_aktywny).max_szarosc)
				{
					liczba_rzeczywiscie_zaszumionych += 1;
				}
			}
		}

	} while (liczba_rzeczywiscie_zaszumionych <= liczba_zaszumionych_pikseli);
}


void filtr_medianowy(struct plik_grafika **obraz_aktywny)
{
	int i, j, k, x, m, n, zmiana;

	struct plik_grafika *obraz_pomocniczy;
	obraz_pomocniczy = malloc(1 * sizeof(struct plik_grafika));
	*obraz_pomocniczy = **obraz_aktywny;
	int **tab_po_filtracji = NULL;                                    
	int ilosc_filtrow_w_rzedzie, ilosc_filtrow_w_kolumnie;
	ilosc_filtrow_w_rzedzie = (**obraz_aktywny).szerokosc - 2;
	ilosc_filtrow_w_kolumnie = (**obraz_aktywny).wysokosc - 2;

	int okno[9];                                // okno na wenwetrzne piksele
	int okno2[3];                               // okno na zewnetrzne piksele

	alokuj_2D(&tab_po_filtracji, (**obraz_aktywny).wysokosc, (**obraz_aktywny).szerokosc);

	for (m = 0; m < 2; m++)                                                         //filtr pierwszego i ostatniego rzedu
	{
		if (m == 1)
		{
			m = (**obraz_aktywny).wysokosc - 1;
		}

		for (n = 0; n < ilosc_filtrow_w_rzedzie; n++)
		{
			for (k = 0; k < 3; k++)
			{
				okno2[k] = (*obraz_pomocniczy).tablica[m][n + k];
			}
			do                                                                    // sortowanie b¹belkowe
			{
				zmiana = 0;
				for (j = 0; j < 2; j++)
				{
					if (okno2[j] > okno2[j + 1])
					{
						zmiana += 1;
						x = okno2[j];
						okno2[j] = okno2[j + 1];
						okno2[j + 1] = x;
					}
				}
			} while (zmiana != 0);
				
			tab_po_filtracji[m][(n+1)] = okno2[1];
		}
	}

	for (m = 0; m < 2; m++)                                                         //filtr pierwszeej i ostatniej kolumny
	{
		if (m == 1)
		{
			m = (**obraz_aktywny).szerokosc - 1;
		}

		for (n = 0; n < ilosc_filtrow_w_kolumnie; n++)
		{
			for (k = 0; k < 3; k++)
			{
				okno2[k] = (*obraz_pomocniczy).tablica[n + k][m];
			}
			do                                                                 // sortowanie b¹belkowe
			{
				zmiana = 0;
				for (j = 0; j < 2; j++)
				{
					if (okno2[j] > okno2[j + 1])
					{
						zmiana += 1;
						x = okno2[j];
						okno2[j] = okno2[j + 1];
						okno2[j + 1] = x;
					}
				}
			} while (zmiana != 0);
			tab_po_filtracji[(n+1)][m] = okno2[1];
		}
	}

	k = 0;

	for (m = 0; m < ilosc_filtrow_w_kolumnie; m++)                                     // nalozenie filtru medianowego na wewnetrzne piksele
	{
		for (n = 0; n < ilosc_filtrow_w_rzedzie; n++)
		{
			for (i = m; i < (3 + m); i++)
			{
				for (j = n; j < (3 + n); j++)
				{
					okno[k] = (*obraz_pomocniczy).tablica[i][j];
					k++;
				}
			}
			k = 0;

			do                                // sortowanie b¹belkowe
			{
				zmiana = 0;
				for (j = 0; j < 8; j++)
				{
					if (okno[j] > okno[j + 1])
					{
						zmiana += 1;
						x = okno[j];
						okno[j] = okno[j + 1];
						okno[j + 1] = x;
					}
				}
			} while (zmiana != 0);

			for (i = m; i < (2 + m); i++)
			{
				for (j = n; j < (2 + n); j++)
				{
					tab_po_filtracji[i + 1][j + 1] = okno[4];
				}
			}
		}
	}
	tab_po_filtracji[0][0] = (*obraz_pomocniczy).tablica[0][0];                                                              //przepisanie wartosci, ktorych nie obejmuje zaden filtr
	tab_po_filtracji[0][(*obraz_pomocniczy).szerokosc - 1] = (*obraz_pomocniczy).tablica[0][(*obraz_pomocniczy).szerokosc - 1];
	tab_po_filtracji[(*obraz_pomocniczy).wysokosc - 1][0] = (*obraz_pomocniczy).tablica[(*obraz_pomocniczy).wysokosc - 1][0];
	tab_po_filtracji[(*obraz_pomocniczy).wysokosc - 1][(*obraz_pomocniczy).szerokosc - 1] = (*obraz_pomocniczy).tablica[(*obraz_pomocniczy).wysokosc - 1][(*obraz_pomocniczy).szerokosc - 1];

	for (i = 0; i < (**obraz_aktywny).wysokosc; i++)
	{
		for (j = 0; j < (**obraz_aktywny).szerokosc; j++)
		{
			(**obraz_aktywny).tablica[i][j] = tab_po_filtracji[i][j];
		}
	}
	
	zwolnij_2D(&tab_po_filtracji, (**obraz_aktywny).wysokosc, (**obraz_aktywny).szerokosc);
	free(obraz_pomocniczy);
}


void filtr_Gaussa(struct plik_grafika **obraz_aktywny)
{
	int i, j, suma;
	int **tab_po_filtracji = NULL;
	alokuj_2D(&tab_po_filtracji, (**obraz_aktywny).wysokosc, (**obraz_aktywny).szerokosc);

	for (i = 0; i < (**obraz_aktywny).wysokosc - 2; i++)                       // nalozenie filtru Gaussa na wewnetrzne piksele
	{
		for (int j = 0; j < (**obraz_aktywny).szerokosc - 2; j++)
		{
			suma = (**obraz_aktywny).tablica[i][j] + 2 * (**obraz_aktywny).tablica[i + 1][j] + (**obraz_aktywny).tablica[i + 2][j] + 2 * (**obraz_aktywny).tablica[i][j + 1] + 4 * (**obraz_aktywny).tablica[i + 1][j + 1] + 2 * (**obraz_aktywny).tablica[i + 2][j + 1] + (**obraz_aktywny).tablica[i][j + 2] + 2 * (**obraz_aktywny).tablica[i + 1][j + 2] + (**obraz_aktywny).tablica[i + 2][j + 2];
			tab_po_filtracji[i+1][j+1] = suma / 16;
		}
	}

	for (i = 0; i < (**obraz_aktywny).wysokosc; i++)                          // przepisanie skrajnych pikseli po lewej i po prawej ktorych nie obejmuje filtr
	{
		for (j = 0; j < 2; j++)
		{
			if (j == 2)
			{
				j = (**obraz_aktywny).szerokosc - 1;
			}
			tab_po_filtracji[i][j] = (**obraz_aktywny).tablica[i][j];
		}
	}

	for (i = 0; i < (**obraz_aktywny).szerokosc; i++)                        // przepisanie skrajnie gornych i dolnych pikseli
	{
		for (j = 0; j < 2; j++)
		{
			if (j == 2)
			{
				j = (**obraz_aktywny).wysokosc - 1;
			}
			tab_po_filtracji[j][i] = (**obraz_aktywny).tablica[j][i];
		}
	}

	for (i = 0; i < (**obraz_aktywny).wysokosc; i++)
	{
		for (j = 0; j < (**obraz_aktywny).szerokosc; j++)
		{
			(**obraz_aktywny).tablica[i][j] = tab_po_filtracji[i][j];
		}
	}

	zwolnij_2D(&tab_po_filtracji, (**obraz_aktywny).wysokosc, (**obraz_aktywny).szerokosc);
}

int wczytaj_int(int * liczba)
{
	int number;
	if (scanf("%d", &number) != 1)
	{
		scanf("%*s");
		return 0;
	}
	else
	{
		*liczba = number;
	}
	return 1;
}

void idioto_ochrona(int * liczba)
{
	while (wczytaj_int(liczba) != 1)
	{
		printf("Wprowadzona wartosc jest niepoprawna. Podaj liczbe calkowita z dostepnego zakresu:\n");
	}
}