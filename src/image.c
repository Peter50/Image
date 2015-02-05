#include <stdio.h>
#include <stdlib.h>

#include "image.h"

struct sPixel{

	int * valeur; 
	Couleur couleur;
};

Pixel initPixel(Couleur couleur){

	Pixel pixel=malloc(sizeof(struct sPixel));
	pixel->couleur=couleur;
	if(couleur == NOIR || couleur == BIN){
		pixel->valeur=malloc(sizeof(int));
	}
	else if(couleur == COULEUR){
		pixel->valeur=malloc(3*sizeof(int));
	}
	return pixel;
}

void detruirePixel(Pixel pixel){

	free(pixel->valeur);
	free(pixel);
}


void setValeurPixel(Pixel pixel,unsigned char * valeur){
	if(pixel->couleur==COULEUR){
		pixel->valeur[0]=valeur[0];
		pixel->valeur[1]=valeur[1];
		pixel->valeur[2]=valeur[2];
	}
	else if(pixel->couleur==NOIR || pixel->couleur==BIN){
		pixel->valeur[0]=valeur[0];
	}
}

unsigned char getValeurPixel(Pixel pixel,int couleur){
	if(pixel->couleur == NOIR || pixel->couleur == BIN){
		return pixel->valeur[0];
	}
	if(pixel->couleur == COULEUR && couleur >= 0 && couleur <= 2){
		return pixel->valeur[couleur];
	}

	return 0;
}

void infoPixel(Pixel pixel){
	printf("Couleur=%d ",pixel->couleur);
	if(pixel->couleur==NOIR || pixel->couleur==BIN){
		printf("Valeur=%d",pixel->valeur[0]);
	}
	else if(pixel->couleur == COULEUR){
		printf("Valeurs:%d,%d,%d",pixel->valeur[0],pixel->valeur[1],pixel->valeur[2]);
	}
	printf("\n");
}

struct sImage{

	int largeur;
	int hauteur;
	int valMax;
	Pixel ** pixel;
};

Image initImage(void){

	Image image=malloc(sizeof(struct sImage));

	image->largeur=0;
	image->hauteur=0;
	image->valMax=0;
	image->pixel=NULL;

	return image;
}

void detruireImage(Image image){

	int i,j;
	for(i=0;i<image->hauteur;i++){
		for(j=0;j<image->largeur;j++){
			detruirePixel(image->pixel[i][j]);
		}
		free(image->pixel[i]);
	}
	free(image->pixel);
	free(image);
}

void initPixelImage(Image image,int largeur,int hauteur, Couleur couleur){

	int i,j;
	image->largeur=largeur;
	image->hauteur=hauteur;

	image->pixel=malloc(hauteur*sizeof(Pixel *));
	for(i=0;i<hauteur;i++){
		image->pixel[i]=malloc(largeur*sizeof(struct sPixel));
		for(j=0;j<largeur;j++){
			image->pixel[i][j]=initPixel(couleur);
		}
	}

}

void infoImage(Image image){

	int i,j;

	printf("Largeur = %d\tHauteur = %d\tValeur max = %d\n",image->largeur,image->hauteur,image->valMax);
	for(i=0;i<image->hauteur;i++){
		for(j=0;j<image->largeur;j++){
			infoPixel(image->pixel[i][j]);
		}
		printf("\n");
	}

}

Image chargerImage(char * fichier){

	FILE * file = NULL;
	unsigned char tmp;
	Couleur couleur;
	int type,largeur,hauteur,pixel;
	int state=0,i=0,j=0,val=0;
	unsigned int pval[3]={0,0,0};
	unsigned char pchar[3]={0,0,0};

	file=fopen(fichier,"r");

	Image image=initImage();

	do{
		tmp=fgetc(file);
		pchar[0]=0;
		pchar[1]=0;
		pchar[2]=0;
		if(state != 3 && tmp == '#'){
			do{
				tmp=fgetc(file);
			}while(tmp != '\n');
		}
		else if(tmp =='P' && state==0){
			tmp=fgetc(file);
			type=tmp-'0';
			if(type == 6 || type == 3){
				couleur=COULEUR;
			}
			else if(type == 5 || type == 2){
				couleur=NOIR;
			}
			else if(type == 4 || type == 1){
				couleur=BIN;
			}
			state++;
		}
		else if(state == 1 && tmp>= '0' && tmp<='9'){
			fseek(file, -1, SEEK_CUR);
			fscanf(file,"%d %d",&largeur,&hauteur);
			initPixelImage(image,largeur,hauteur,couleur);			
			state++;
		}
		else if(state == 2 && tmp>='0' && tmp <='9'){
			fseek(file,-1,SEEK_CUR);
			fscanf(file,"%d",&pixel);
			image->valMax=pixel;
			tmp=fgetc(file);
			state++;
		}
		else if(state == 3){
			if(tmp >=0 && tmp <=9 && type==2){
				val=0;
				fseek(file,-1,SEEK_CUR);
				fscanf(file,"%d",&val);
				tmp=val;
				setValeurPixel(image->pixel[i][j],&tmp);
				j++;
				if(j>=largeur){
					j=0;
					i++;
					if(i>=hauteur){
						state++;
					}
				}
			}
			else if(type == 5){
				setValeurPixel(image->pixel[i][j],&tmp);
				j++;
				if(j>=largeur){
					j=0;
					i++;
					if(i>=hauteur){
						state++;
					}
				}
			}
			else if(tmp >=0 && tmp <=9 && type == 3){
				val=0;
				fseek(file,-1,SEEK_CUR);
				fscanf(file,"%u %u %u",&pval[0],&pval[1],&pval[2]);
				pchar[0]=pval[0];
				pchar[1]=pval[1];
				pchar[2]=pval[2];
				setValeurPixel(image->pixel[i][j],pchar);
				j++;
				if(j>=largeur){
					j=0;
					i++;
					if(i>=hauteur){
						state++;
					}
				}
			}
			else if(type == 6){
				pchar[0]=tmp;
				tmp=fgetc(file);
				pchar[1]=tmp;
				tmp=fgetc(file);
				pchar[2]=tmp;
				setValeurPixel(image->pixel[i][j],pchar);
				j++;
				if(j>=largeur){
					j=0;
					i++;
					if(i>=hauteur){
						state++;
					}
				}
			}
		}	
	}while(!feof(file));

	fclose(file);

	return image;
}

void sauverImage(Image image, char * fichier,Codage codage, Couleur couleur){

	FILE * file=NULL;
	file = fopen(fichier,"w");

	int i,j;
	
	if(couleur == NOIR && codage == BINAIRE){
		fprintf(file,"P5\n");	
	}
	else if(couleur == NOIR && codage == DECIMAL){
		fprintf(file,"P2\n");
	}
	else if(couleur == COULEUR && codage == BINAIRE){
		fprintf(file,"P6\n");
	}
	else if(couleur == COULEUR && codage ==DECIMAL){
		fprintf(file,"P3\n");
	}
	else if(couleur == BIN && codage == BINAIRE){
		fprintf(file,"P4\n");
	}
	else if(couleur == BIN && codage == DECIMAL){
		fprintf(file,"P1\n");
	}

	fprintf(file,"%d %d\n",image->largeur,image->hauteur);
	fprintf(file,"%d\n",image->valMax);
	
	for(i=0;i<image->hauteur;i++){
		for(j=0;j<image->largeur;j++){
			if((couleur == NOIR || couleur == BIN) && codage == DECIMAL){ 
				fprintf(file,"%d\t",getValeurPixel(image->pixel[i][j],0));
			}
			else if((couleur == NOIR || couleur == BIN)&& codage == BINAIRE){
				fprintf(file,"%c",getValeurPixel(image->pixel[i][j],0));
			}
			else if(couleur == COULEUR && codage == DECIMAL){
				fprintf(file,"%d %d %d\t",getValeurPixel(image->pixel[i][j],0),getValeurPixel(image->pixel[i][j],1),getValeurPixel(image->pixel[i][j],2));
			}
			else if(couleur == COULEUR && codage == BINAIRE){
				fprintf(file,"%c%c%c",getValeurPixel(image->pixel[i][j],0),getValeurPixel(image->pixel[i][j],1),getValeurPixel(image->pixel[i][j],2));
			}
		}
		if(codage == DECIMAL){
			fprintf(file,"\n");
		}
	}

	fclose(file);

}
