#include <stdio.h>

void main()
{
    int n = 0;      // Processes Number
    int CPU_CT = 0; // CPU_CT Current time
    // int allTime = 0; // Time neded to finish all processes
    printf("Enter number of Processes : ");
    scanf("%d", &n);

    int AT[n];
    int BT[n]; // Processes Time // BT
    int PP[n]; // Processes piriorty
    int turnaroundTime[n];
    int waittingTime[n];

    int ATt[n];
    int NoP = n;

    // Scanning Time and Piriorty
    for (int i = 0; i < n; i++)
    {
        printf("\nAT for P%d: ", i + 1);
        scanf("%d", &AT[i]);
        printf("BT for P%d: ", i + 1);
        scanf("%d", &BT[i]);
        printf("Piriorty for P%d: ", i + 1);
        scanf("%d", &PP[i]);
        ATt[i] = AT[i];
    }

    int LAT = 0; // LastArrivalTime
    for (int i = 0; i < n; i++)
        if (AT[i] > LAT)
            LAT = AT[i];

    int ATv = AT[0]; // Pointing to Arrival Time Value
    int ATi = 0;     // Pointing to Arrival Time indix
    int P1 = PP[0];  // Pointing to 1st piriorty Value
    int P2 = PP[0];  // Pointing to 2nd piriorty Value

    // findding the First Arrival Time and Highst piriorty Process

    while (NoP > 0 && CPU_CT <= 1000)
    {

        // for finding smallest priority for AT < CPU_CT
        for (int i = 0; i < n; i++)
        {
            if (ATt[i] < ATv)
            {
                ATi = i;
                ATv = ATt[i];

                P1 = PP[i];
                P2 = PP[i];
            }
            else if (ATt[i] == ATv || ATt[i] <= CPU_CT)
            {
                if (PP[i] != (n + 1))
                    P2 = PP[i];
                if (P2 < P1)
                {
                    ATi = i;
                    ATv = ATt[i];
                    P1 = PP[i];
                    P2 = PP[i];
                }
            }
        }

        if (CPU_CT < ATv)
        {
            CPU_CT = CPU_CT + 1;
            continue;
        }
        else
        {

            waittingTime[ATi] = CPU_CT - ATt[ATi];
            CPU_CT = CPU_CT + BT[ATi];
            turnaroundTime[ATi] = CPU_CT - ATt[ATi];
            PP[ATi] = n + 1;
            P1 = PP[0]; // Pointing to 1st piriorty Value
            P2 = PP[0]; // Pointing to 2nd piriorty Value
            ATi = 0;    // Pointing to Arrival Time indix
            NoP = NoP - 1;

            // setting ATi[Ati] and ATv same so ATt[ATi] never get selected again
            ATt[ATi] = LAT + 10;
            ATv = LAT + 10; // Pointing to Arrival Time Value
        }
    }

    printf("\n\nn\tBT\tPP\tTAT\tWT\n\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\n", i + 1, BT[i], PP[i], turnaroundTime[i], waittingTime[i]);
    }

    float AvgWT = 0;
    float AVGTaT = 0;
    for (int i = 0; i < n; i++)
    {
        AvgWT = waittingTime[i] + AvgWT;
        AVGTaT = turnaroundTime[i] + AVGTaT;
    }

    printf("Avg. Turnaround Time = %.2f\nAvg. Waitting Time = %.2f\n", AVGTaT / n, AvgWT / n);
}