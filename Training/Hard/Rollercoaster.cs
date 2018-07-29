using System;
using System.Collections.Generic;

public class Solution{
    #region Classes
    public struct Group : IEquatable<Group>{
        #region Champs
        public readonly int id;
        public readonly int membres;
        #endregion

        #region Constructeur
        public Group(int id, int membres){
            this.id = id;
            this.membres = membres;
        }
        #endregion

        #region Méthodes
        public override bool Equals(object obj){
            if (obj is Group){
                return Equals((Group)obj);
            }
            return false;
        }
        public bool Equals(Group groupe){
            return this.id.Equals(groupe.id);
        }
        public override int GetHashCode(){
            return this.id;
        }
        #endregion

        #region Operations
        public static bool operator ==(Group a, Group b){
            return a.id == b.id;
        }
        public static bool operator !=(Group a, Group b){
            return a.id != b.id;
        }
        #endregion
    }

    public struct QueueInfo{
        #region Champs
        public readonly int next;
        public readonly int profit;
        #endregion
        #region Constructeur
        public QueueInfo(int next, int profit){
            this.next = next;
            this.profit = profit;
        }
        #endregion
    }
    #endregion

    #region Méthodes
    private static void Main(){
        string[] inputs = Console.ReadLine().Split(' ');
        int size = int.Parse(inputs[0]);    //Taille de l'attraction
        int count = int.Parse(inputs[1]);   //Manèges/jour
        int n = int.Parse(inputs[2]);       //Nombre de groupes dans la queue
        Group[] queue = new Group[n];
        //Récupération des groupees
        for (int i = 0; i < n; i++){
            queue[i] = new Group(i, int.Parse(Console.ReadLine()));
        }
        Dictionary<Group, QueueInfo> groupeInfo = new Dictionary<Group, QueueInfo>(n);
        long profits = 0L;  // Profit total
        int index = 0;      // Index de la queue
        for (int rides = 0; rides < count; rides++){
            Group groupe = queue[index];
            QueueInfo info;
            if (groupeInfo.TryGetValue(groupe, out info)){
                index = info.next;
                profits += info.profit;
            }
            else{
                int total = groupe.membres;
                int j = 0;
                Group g;
                // Identification de l'info du groupe
                for (int i = index + 1; i < index + n; i++){
                    j = i % n;
                    g = queue[j];
                    if (total + g.membres > size) { break; }
                    total += g.membres;
                }
                index = j;
                profits += total;
                groupeInfo.Add(groupe, new QueueInfo(j, total));
            }
        }
        Console.WriteLine(profits);
    }
    #endregion
}
