#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double TempoConversion(double tempo, int game1, int game2);

int main()
{
    double tempo;
    double tempo2;
    int source_game;
    int destination_game;
    printf("Hello, and welcome to Inferno's little Sonic SMPS tempo convertor program.\n\nEnter your base tempo in decimal (excluding the tempo divisor, should be a whole number): ");
    scanf("%lf", &tempo);
    printf("Enter the game you are converting from (1 for Sonic 1, 2 for Sonic 2, 3 for Sonic 3 and related games): ");
    scanf("%d", &source_game);
    if(source_game < 1 || source_game > 3)
    {
        printf("Invalid source game ID! Please try again.\n");
        system("pause");
        exit(0);
    }
    printf("Enter the game you are converting to (1 for Sonic 1, 2 for Sonic 2, 3 for Sonic 3 and related games): ");
    scanf("%d", &destination_game);
    if(destination_game < 1 || destination_game > 3)
    {
        printf("Invalid destination game ID! Please try again.\n");
        system("pause");
        exit(0);
    }
    if(source_game == destination_game)
    {
        printf("Your two game IDs are identical.\n");
        system("pause");
        exit(0);
    }
    if (source_game == 1 && destination_game == 2 && tempo == 0) // Required part of conversion
    {
        tempo = 256;
    }
    tempo2 = TempoConversion(tempo, source_game, destination_game);
    printf("\nYour converted tempo (in decimal): %.0f\n", tempo2);
    system("pause");
    return 0;
}

double TempoConversion(double tempo, int game1, int game2)
{
    double tempo_alt = tempo;
    double tempo_temp = tempo;
    if (game1 == 1) // Sonic 1 case
    {
        // Since we know that our destination will HAVE to be either S2 or S3, do the S1 -> S2 conversion no matter what
        tempo_temp = floor(((tempo - 1) * 256 + floor(tempo/2)) / tempo);
        // Shared S2->S3 tempo calculation
        if (game2 == 3)
        {
            // S3 tempo = (256 - S2 Tempo) % 256
            tempo_alt = fmod((256 - tempo_temp), 256);
        }
        else {
            tempo_alt = tempo_temp;
        }
    }
    if (game1 == 2) // Sonic 2 case
    {
        if (game2 == 1) // The dogshit approximation you were warned about!
        {
            // S1 main tempo = floor{ floor[ (768 - S2 main tempo)/2 ] / (256 - S2 main tempo) }
            tempo_alt = floor(floor((768 - tempo) / 2) / (256 - tempo));
        }
        // Shared S2->S3 tempo calculation
        if (game2 == 3)
        {
            // S3 tempo = (256 - S2 Tempo) % 256
            
            tempo_alt = fmod((256 - tempo), 256);
        }
    }
    if (game1 == 3) // Sonic 3 case
    {
        // In order to convert to S1, we'd need to convert through S2 anyways. Do the conversion by default.
        // S2 main tempo = (256 - S3 main tempo) mod 256
        tempo_temp = fmod((256 - tempo), 256);
        if (game2 == 1) // The dogshit approximation you were warned about!
        {
            // S1 main tempo = floor{ floor[ (768 - S2 main tempo)/2 ] / (256 - S2 main tempo) }
            tempo_alt = floor(floor((768 - tempo_temp) / 2) / (256 - tempo_temp));
        }
        else {
            tempo_alt = tempo_temp;
        }
    }

    return tempo_alt;
}